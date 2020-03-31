#ifndef _tiledmap_h_
#define _tiledmap_h_

#include "spriteframes.h"
#include "tilecodes.h"
#include "tile.h"

// Tiled map attributes
#define MAP_WIDTH 					19
#define MAP_HEIGHT					13

typedef struct tiledMap {
	Tile tiles[MAP_HEIGHT][MAP_WIDTH];
} TiledMap;

TiledMap* initTiledMap();

char getTile(TiledMap* tiledMap, int x, int y);
void drawTile(unsigned short int x, unsigned short int y, unsigned short int xImage, unsigned short int yImage);

void getTileSpriteFrame(TiledMap* tiledMap, int x, int y, unsigned short int* imgCoord);

void createBomb(TiledMap* tiledMap, char x, char y, char player);
void createExplosion(TiledMap* tiledMap, char x, char y, char size);

void animateTiles(TiledMap* tiledMap);
void animateExplosionTile(TiledMap* tiledMap, char x, char y);
void animateBombTile(TiledMap* tiledMap, char x, char y);

#endif
