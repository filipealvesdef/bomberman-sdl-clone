#include "mainMenuScene.h"

extern Scene* scene;

Scene* createMainMenuScene() {
	Scene* mainMenuScene = createScene(&update, &draw);

    Sprite* arrow = createSprite(WIDTH / 2 - MENU_WIDTH / 2 - ARROW_WIDTH - ARROW_MARGIN_RIGHT, HEIGHT - MENU_HEIGHT - MENU_MARGIN_BOTTOM, SF_ARROW);
    Sprite* logoTop = createSprite(-LOGO_WIDTH - LOGO_VEL_ANIMATION - 8, LOGO_MARGIN_TOP, SF_LOGO_TOP);
    Sprite* logoBottom = createSprite(WIDTH, LOGO_MARGIN_TOP + LOGO_TOP_HEIGHT, SF_LOGO_BOTTOM);

    Sprite* baloon = createSprite(20, 20, SF_BALOON);
    baloon->dir[0] = 0;
    baloon->dir[1] = -1;

    Sprite* bigZeppelin = createSprite(WIDTH - BIG_ZEPPELIN_WIDTH - BIG_ZEPPELIN_MARGIN_RIGHT, HEIGHT / 2 - BIG_ZEPPELIN_HEIGHT / 2, SF_BIG_ZEPPELIN);
    Sprite* littleZeppelin = createSprite(WIDTH / 4, HEIGHT / 2 + 2 * LITTLE_ZEPPELIN_HEIGHT, SF_LITTLE_ZEPPELIN);

    addChild(mainMenuScene, baloon);
    addChild(mainMenuScene, bigZeppelin);
    addChild(mainMenuScene, littleZeppelin);

    addChild(mainMenuScene, logoTop);
    addChild(mainMenuScene, logoBottom);

    addChild(mainMenuScene, arrow);   

	return mainMenuScene;
}

static void update(Scene* scene) {

    Sprite* baloon = (Sprite*) getData(scene->nodes, 0);
    Sprite* bigZeppelin = (Sprite*) getData(scene->nodes, 1);     
    Sprite* littleZeppelin = (Sprite*) getData(scene->nodes, 2); 

    Sprite* logoTop = (Sprite*) getData(scene->nodes, 3);
    Sprite* logoBottom = (Sprite*) getData(scene->nodes, 4);    
    
    Sprite* arrow = (Sprite*) getData(scene->nodes, 5); 

	// Logo animation
    if (logoBottom->x > WIDTH / 2 - LOGO_WIDTH / 2) {
        logoBottom->x -= LOGO_VEL_ANIMATION;
        logoTop->x += LOGO_VEL_ANIMATION;
    }

    // Zeppelins animation
    bigZeppelin->x -= 0.3;
    littleZeppelin->x += 0.2;

    // baloon animation
    baloon->x += 0.1;
    baloon->y += 0.05 * baloon->dir[1];

    if (baloon->y >= 22.1 || baloon->y <= 17.9)
        baloon->dir[1] *= -1;
    
    if (pushButtons[KEY1] || pushButtons[KEY2]) {
    	/*clearLCD();
    	turnOffGreenLeds();
        turnOffRedLeds();*/

        if (pushButtons[KEY2]) {
            pushButtons[KEY2] = 0;
        
            if (arrow->y > HEIGHT - MENU_MARGIN_BOTTOM - 2 * ARROW_HEIGHT - 2)
                arrow->y -= ARROW_HEIGHT + 1;
        }

        if (pushButtons[KEY1]) {
            pushButtons[KEY1] = 0;

            if (arrow->y < HEIGHT - MENU_MARGIN_BOTTOM - ARROW_HEIGHT - 1) 
                arrow->y += ARROW_HEIGHT + 1;
        }

    	/*switch (arrow->y) {
        	case HEIGHT - MENU_HEIGHT - MENU_MARGIN_BOTTOM:
        		writeLCD(0, 0, "Not working...");
        		break;

        	case HEIGHT - MENU_HEIGHT - MENU_MARGIN_BOTTOM + ARROW_HEIGHT + 1:
        		writeLCD(0, 0, "Press key 3");
        		writeLCD(0, 1, "to start");
        		break;

        	case HEIGHT - MENU_HEIGHT - MENU_MARGIN_BOTTOM + 2 * ARROW_HEIGHT + 2:
        		writeLCD(0, 0, "Enter a password");
        		writeLCD(0, 1, "Then press key 3");
        		break;
        }*/
    }

    if (pushButtons[KEY3]) {
        pushButtons[KEY3] = 0;
        /*clearLCD();
        turnOffGreenLeds();
        turnOffRedLeds();*/
        
        if (arrow->y == HEIGHT - MENU_HEIGHT - MENU_MARGIN_BOTTOM) {
            //writeLCD(0, 0, "Invalid option");
        }

        else if (arrow->y == HEIGHT - MENU_HEIGHT - MENU_MARGIN_BOTTOM + ARROW_HEIGHT + 1)
            goToPlayingScene();

        /*else if(arrow->y == HEIGHT - MENU_HEIGHT - MENU_MARGIN_BOTTOM + 2 * ARROW_HEIGHT + 2) {
            switch (getSwitchInput()) {
            	case PASS_P1_SPEED:
            		writeLCD(0, 0, "P1 double speed");
            		p1DoubleSpeed = 2;
        			turnOnGreenLeds();
        			break;

        		case PASS_P2_SPEED:
        			writeLCD(0, 0, "P2 double speed");
        			p2DoubleSpeed = 2;
        			turnOnGreenLeds();
        			break;


        		default:
        			writeLCD(0, 0, "Incorrect pass!");
        			turnOnRedLeds();
            }
        }
        */
        
    }

   	//if (frames % TIME_BLINK_7_SEG == 0)
   	//	blink7Seg();
}

static void draw(Scene* scene) {

    // blue background
	fillRect(0, 0, 320, 124, 0x001e);

    // background spr
    drawImage(0, 124, SF_BACKGROUND);

    int i;
    for (i = 0; i < scene->nodes->size; i++)  {
        Sprite* spr = (Sprite*) getData(scene->nodes, i);
        drawImage((int) spr->x, (int) spr->y, spr->xImage, spr->yImage, spr->width, spr->height);
    }

    // menu
    drawImage(WIDTH / 2 - MENU_WIDTH / 2, HEIGHT - MENU_HEIGHT - MENU_MARGIN_BOTTOM, SF_MENU);

    // swapBuffers();
}

void goToPlayingScene() {
    deleteScene(scene);
    scene = createPlayingScene();
}
