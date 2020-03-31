#ifndef _player_h_
#define _player_h_

#include "spriteframes.h"
#include "constants.h"
#include "tiledMap.h"

// Player attributes
#define	WHITE_PLAYER_ID					0
#define	BLACK_PLAYER_ID					1

#define PLAYER_WIDTH					16
#define	PLAYER_HEIGHT					24

#define PLAYER_STATES					5
#define PLAYER_FRAMES					4

#define ANIMATION_WALKING_DOWN			0
#define ANIMATION_WALKING_LEFT			1
#define ANIMATION_WALKING_RIGHT			2
#define ANIMATION_WALKING_UP			3
#define ANIMATION_DYING					4

#define PLAYER_INIT_VELOCITY			2

#define FRAMES_PLAYER_ANIMATION_WALK	3
#define FRAMES_PLAYER_ANIMATION_DYING	15

#define FRAMES_DELAY_REALIVEPLAYER		FPS << 1

#define WALK_UP_KEY						0
#define WALK_DOWN_KEY					1
#define WALK_LEFT_KEY					2
#define WALK_RIGHT_KEY					3
#define BOMB_KEY						4

#define DIR_UP							0
#define DIR_DOWN						1
#define DIR_LEFT						2
#define DIR_RIGHT						3

typedef struct player {
    int x;
    int y;
    char animation;
    char frame;
    unsigned char velocity;
    char id;
    unsigned char commands[5];
} Player;

Player* createPlayer(char id);
void getCenterTileCoord(Player* player, char* tileCoord);
void getTileCoord(Player* player, char dx, char dy, char* tileCoord);
void deletePlayer(Player* player);
void resetPlayer(Player* player);
void walk(Player* player, TiledMap* tiledMap, char dir);
void drawPartialTiles(Player* player, TiledMap* tiledMap);
void drawPlayer(Player* player, TiledMap* tiledMap);

#endif
