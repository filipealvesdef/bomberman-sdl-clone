#include "tiledmap.h"
#include <stdlib.h>

extern unsigned int frames;

static unsigned char bombAnimationFrames[QNT_FRAMES_BOMB_ANIMATION] = {
    Y_BOMB_0, Y_BOMB_1, Y_BOMB_2, Y_BOMB_1
};

static unsigned char explosionAnimationFrames[QNT_FRAMES_EXPLOSION_ANIMATION][2] = {
    {SF_EXPLOSION_LEFT_0}, {SF_EXPLOSION_LEFT_1}, {SF_EXPLOSION_LEFT_2}, {SF_EXPLOSION_LEFT_3}, {SF_EXPLOSION_LEFT_4},
    {SF_EXPLOSION_RIGHT_0}, {SF_EXPLOSION_RIGHT_1}, {SF_EXPLOSION_RIGHT_2}, {SF_EXPLOSION_RIGHT_3}, {SF_EXPLOSION_RIGHT_4},
    {SF_EXPLOSION_CENTER_0}, {SF_EXPLOSION_CENTER_1}, {SF_EXPLOSION_CENTER_2}, {SF_EXPLOSION_CENTER_3}, {SF_EXPLOSION_CENTER_4},
    {SF_EXPLOSION_TOP_0}, {SF_EXPLOSION_TOP_1}, {SF_EXPLOSION_TOP_2}, {SF_EXPLOSION_TOP_3}, {SF_EXPLOSION_TOP_4},
    {SF_EXPLOSION_BOTTOM_0}, {SF_EXPLOSION_BOTTOM_1}, {SF_EXPLOSION_BOTTOM_2}, {SF_EXPLOSION_BOTTOM_3}, {SF_EXPLOSION_BOTTOM_4},
    {SF_EXPLOSION_MID_TOP_0}, {SF_EXPLOSION_MID_TOP_1}, {SF_EXPLOSION_MID_TOP_2}, {SF_EXPLOSION_MID_TOP_3}, {SF_EXPLOSION_MID_TOP_4},
    {SF_EXPLOSION_MID_BOTTOM_0}, {SF_EXPLOSION_MID_BOTTOM_1}, {SF_EXPLOSION_MID_BOTTOM_2}, {SF_EXPLOSION_MID_BOTTOM_3}, {SF_EXPLOSION_MID_BOTTOM_4},
    {SF_EXPLOSION_MID_RIGHT_0}, {SF_EXPLOSION_MID_RIGHT_1}, {SF_EXPLOSION_MID_RIGHT_2}, {SF_EXPLOSION_MID_RIGHT_3}, {SF_EXPLOSION_MID_RIGHT_4},
    {SF_EXPLOSION_MID_LEFT_0}, {SF_EXPLOSION_MID_LEFT_1}, {SF_EXPLOSION_MID_LEFT_2}, {SF_EXPLOSION_MID_LEFT_3}, {SF_EXPLOSION_MID_LEFT_4} 
};

TiledMap* initTiledmap() {
    int i, j;
    srand(frames);

    TiledMap* tiledMap = (TiledMap*) malloc(sizeof(TiledMap));

    for (i = 0; i < MAP_HEIGHT; i++) {
        for (j = 0; j < MAP_WIDTH; j++) {
            if (i == 0 || j == 0 || j == MAP_WIDTH - 1 || i == MAP_HEIGHT - 1) {
                tiledMap->tiles[i][j].code = SOLID_TILE;
            	drawTile(j, i, SF_SOLID_TILE);
            }

            else if ((j % 2 == 0 && i % 2 == 0)) {
                tiledMap->tiles[i][j].code = SOLID_TILE;
                drawTile(j, i, SF_SOLID_TILE);

                if (rand() % 2 == 0) {
                    tiledMap->tiles[i + 1][j].code = SHADOW_GRASS_TILE;
                    drawTile(j, i + 1, SF_SHADOW_GRASS_TILE);
                }

                else {
                    tiledMap->tiles[i + 1][j].code = BRICK_TILE;
                    drawTile(j, i + 1, SF_BRICK_TILE);
                }
            }

            else if (tiledMap->tiles[i][j].code != SHADOW_GRASS_TILE) {
                if (rand() % 4 == 0 || (i == 1 && (j == 1 || j == 2))
                    || (i == 2 && j == 1) || (i == MAP_HEIGHT - 2 && (j == MAP_WIDTH - 2 || j == MAP_WIDTH - 3))
                    || (i == MAP_HEIGHT - 3 && (j == MAP_WIDTH - 2))) {

                    tiledMap->tiles[i][j].code = GRASS_TILE;
                    drawTile(j, i, SF_GRASS_TILE);
                }

                else {
                    tiledMap->tiles[i][j].code = BRICK_TILE;
                    drawTile(j, i, SF_BRICK_TILE);
                }

            }
        }
    }

    return tiledMap;
}

void drawTile(unsigned short int x, unsigned short int y, unsigned short int xImage, unsigned short int yImage) {
	drawImage((x << 4) + 8, (y << 4) + 32, xImage, yImage, TILE_SIZE, TILE_SIZE);
}

void getTileSpriteFrame(TiledMap* tiledMap, int x, int y, unsigned short int* imgCoord) {
    imgCoord[1] = 107;

    switch (tiledMap->tiles[y][x].code) {
        case SOLID_TILE:
            imgCoord[0] = 0;
            break;

        case BRICK_TILE:
            imgCoord[0] = 17;
            break;

        case SHADOW_GRASS_TILE:
            imgCoord[0] = 34;
            break;

        case GRASS_TILE:
            imgCoord[0] = 51;
            break;

        case BOMB_TILE:
            imgCoord[0] = X_BOMB;
            imgCoord[1] = bombAnimationFrames[tiledMap->tiles[y][x].frame];
            break;
    }
}

char getTile(TiledMap* tiledMap, int x, int y) {
    x = (x - 8) >> 4;
    y = (y - 32) >> 4;

    return tiledMap->tiles[y][x].code;
}

void animateTiles(TiledMap* tiledMap) {
    int i, j;

    for (i = 0; i < MAP_HEIGHT; i++) {
        for (j = 0; j < MAP_WIDTH; j++) {
            if (tiledMap->tiles[i][j].code == EXPLOSION_TILE && frames % FRAMES_EXPLOSION_ANIMATION == 0) {
                animateExplosionTile(tiledMap, j, i);
            }

            else if (tiledMap->tiles[i][j].code == BOMB_TILE && frames % FRAMES_BOMB_ANIMATION == 0) {
                animateBombTile(tiledMap, j, i);
            }            
        }
    }
}

void createBomb(TiledMap* tiledMap, char x, char y, char player) {
    if (~tiledMap->tiles[y][x].code & 0x1) {

        tiledMap->tiles[y][x].code = BOMB_TILE;
        tiledMap->tiles[y][x].frame = 0;
        tiledMap->tiles[y][x].cycles = 0;

        drawTile(x, y, SF_BOMB_TILE_0);
    }
}

void animateBombTile(TiledMap* tiledMap, char x, char y) {
    tiledMap->tiles[y][x].frame = (tiledMap->tiles[y][x].frame + 1) % QNT_FRAMES_BOMB_ANIMATION;

    if (tiledMap->tiles[y][x].frame == 0) 
        tiledMap->tiles[y][x].cycles++;

    if (tiledMap->tiles[y][x].cycles == CYCLES_TO_EXPLODE)
        createExplosion(tiledMap, x, y, 2);

    else
        drawTile(x, y, X_BOMB, bombAnimationFrames[tiledMap->tiles[y][x].frame]);
}

void createExplosion(TiledMap* tiledMap, char x, char y, char size) {

    tiledMap->tiles[y][x].code = EXPLOSION_TILE;
    tiledMap->tiles[y][x].frame = EXPLOSION_CENTER_0;

    if (tiledMap->tiles[y - size][x].code != SOLID_TILE && tiledMap->tiles[y - size + 1][x].code != SOLID_TILE) {
        tiledMap->tiles[y - size][x].code = EXPLOSION_TILE;
        tiledMap->tiles[y - size][x].frame = EXPLOSION_TOP_0;
    }

    if (tiledMap->tiles[y + size][x].code != SOLID_TILE && tiledMap->tiles[y + size - 1][x].code != SOLID_TILE) {
        tiledMap->tiles[y + size][x].code = EXPLOSION_TILE;
        tiledMap->tiles[y + size][x].frame = EXPLOSION_BOTTOM_0;
    }

    if (tiledMap->tiles[y][x + size].code != SOLID_TILE && tiledMap->tiles[y][x + size - 1].code != SOLID_TILE) {
        tiledMap->tiles[y][x + size].code = EXPLOSION_TILE;
        tiledMap->tiles[y][x + size].frame = EXPLOSION_RIGHT_0;
    }

    if (tiledMap->tiles[y][x - size].code != SOLID_TILE && tiledMap->tiles[y][x - size + 1].code != SOLID_TILE) {
        tiledMap->tiles[y][x - size].code = EXPLOSION_TILE;
        tiledMap->tiles[y][x - size].frame = EXPLOSION_LEFT_0;
    }

    int i;
    for (i = 1; i < size; i++) {
        if (tiledMap->tiles[y + i][x].code == SOLID_TILE)
            break;

        tiledMap->tiles[y + i][x].code = EXPLOSION_TILE;
        tiledMap->tiles[y + i][x].frame = EXPLOSION_MID_BOTTOM_0;
    }

    for (i = 1; i < size; i++) {
        if (tiledMap->tiles[y - i][x].code == SOLID_TILE)
            break;

        tiledMap->tiles[y - i][x].code = EXPLOSION_TILE;
        tiledMap->tiles[y - i][x].frame = EXPLOSION_MID_TOP_0;
    }

    for (i = 1; i < size; i++) {
        if (tiledMap->tiles[y][x + i].code == SOLID_TILE)
            break;

        tiledMap->tiles[y][x + i].code = EXPLOSION_TILE;
        tiledMap->tiles[y][x + i].frame = EXPLOSION_MID_RIGHT_0;
    }

    for (i = 1; i < size; i++) {
        if (tiledMap->tiles[y][x - i].code == SOLID_TILE)
            break;

        tiledMap->tiles[y][x - i].code = EXPLOSION_TILE;
        tiledMap->tiles[y][x - i].frame = EXPLOSION_MID_LEFT_0;
    }

}

void animateExplosionTile(TiledMap* tiledMap, char x, char y) {
    if ((tiledMap->tiles[y][x].frame + 1) % FRAMES_EXPLOSION_STATE == 0) {
        tiledMap->tiles[y][x].code = GRASS_TILE;
        drawTile(x, y, SF_GRASS_TILE);
    }

    else {
        drawTile(x, y, explosionAnimationFrames[tiledMap->tiles[y][x].frame][0], explosionAnimationFrames[tiledMap->tiles[y][x].frame][1]);
        tiledMap->tiles[y][x].frame++;
    }
}
