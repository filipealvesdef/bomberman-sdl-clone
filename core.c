#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h"
#include <time.h>

#include "keyCodes.h"
#include "constants.h"

SDL_Window* window = NULL;
SDL_Surface* surface = NULL;
SDL_Surface* imageSurface = NULL;
extern short int spritesheet[SPR_HEIGHT][SPR_WIDTH];
int currentTime = 0;
SDL_TimerID timerID;
char pushButtons[256];

// core globals
unsigned char keys[256];
//char pushButtons[3] = {0};

char clock_timer[4];
char lives[4];

char running;
unsigned int frames;

#include "core.h"
#include "constants.h"
#include "mainMenuScene.h"

Scene* scene;

Uint32 interruption( Uint32 interval, void* param ) {
    currentTime++;
    return 1;
}

void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel) {
    Uint8 *p = (Uint8*) surface->pixels + y * surface->pitch + x * 2;
    *(Uint16 *)p = pixel;
}

void drawImage(unsigned int xScreen, unsigned int yScreen, int xImage, int yImage, int width, int height) {
    short int i, j;
    for (i = yImage; i < yImage + height; i++) {
        for (j = xImage; j < xImage + width; j++) {
            short int pixel = spritesheet[i][j];

            if ((Uint16) pixel != ALPHA_COLOR && xScreen + j >= 0 && xScreen + (j - xImage) < WIDTH && yScreen + (i - yImage) >= 0 && yScreen + (i - yImage) <= HEIGHT) {
                setPixel(imageSurface, xScreen + (j - xImage), yScreen + (i - yImage), pixel);
            }
        }
    }
}

void fillRect(unsigned short int x, unsigned short int y, unsigned short int width, unsigned short int height, short int color) {
    int i, j;

	for (i = 0; i < width; i++) {
		for (j = 0; j < height; j++)
			setPixel(imageSurface, x + i, y + j, color);
	}
}

void run() {
    unsigned int lastTime = 0, dt = 0;
    double lag = 0;

    while (1) {
        dt = currentTime - lastTime;
        lastTime = currentTime;

        input();

        if (running) {
            lag += dt;

            while (lag >= SPF) {
                scene->update(scene);
                lag -= SPF;
                frames++;
            }

            scene->draw(scene);
        }

        SDL_BlitSurface(imageSurface, NULL, surface, NULL);
        SDL_UpdateWindowSurface(window);
    }
}

void input() {
    SDL_Event ev;

    while (SDL_PollEvent(&ev) != 0) {
        switch (ev.type) {
            case SDL_KEYDOWN:
                // printf("%d", ev.key.keysym.scancode);
                keys[ev.key.keysym.scancode] = 1;

                pushButtons[ev.key.keysym.scancode] = 1;

                break;

            case SDL_KEYUP:
                keys[ev.key.keysym.scancode] = 0;
                pushButtons[ev.key.keysym.scancode] = 0;

                break;
        }
    }
}

int main(int argc, char** argv) {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        printf("SDL_Error: %s", SDL_GetError());
    }

    else {
        window = SDL_CreateWindow("Bomberman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
        timerID = SDL_AddTimer(1, interruption, "" );

        if (window == NULL) {
            printf("SDL_Error: %s", SDL_GetError());
        }

        else {
            surface = SDL_GetWindowSurface(window);
            imageSurface = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 16, 0, 0, 0, 0);

            frames = 0;
            running = 1;
            scene = createMainMenuScene();

            run();

            SDL_FreeSurface(imageSurface);
            SDL_RemoveTimer( timerID );
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
