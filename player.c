#include "player.h"
#include "tiledmap.h"
#include "keycodes.h"
#include <stdlib.h>

extern unsigned int frames;

static unsigned short int animationFrames[PLAYER_STATES][PLAYER_FRAMES] = {
	{SF_WALKING_DOWN_0, SF_WALKING_DOWN_1, SF_WALKING_DOWN_2, SF_WALKING_DOWN_3},
	{SF_WALKING_LEFT_0, SF_WALKING_LEFT_1, SF_WALKING_LEFT_2, SF_WALKING_LEFT_3},
	{SF_WALKING_RIGHT_0, SF_WALKING_RIGHT_1, SF_WALKING_RIGHT_2, SF_WALKING_RIGHT_3},
	{SF_WALKING_UP_0, SF_WALKING_UP_1, SF_WALKING_UP_2, SF_WALKING_UP_3},
	{SF_WALKING_DYING_0, SF_WALKING_DYING_1, SF_WALKING_DYING_2, SF_WALKING_DYING_3}
};

Player* createPlayer(char id) {
	Player* player = (Player*) malloc(sizeof(Player));

	player->id = id;
	resetPlayer(player);

	switch (id) {
		case WHITE_PLAYER_ID:
			player->commands[WALK_UP_KEY] = KEY_W;
			player->commands[WALK_DOWN_KEY] = KEY_S;
			player->commands[WALK_LEFT_KEY] = KEY_A;
			player->commands[WALK_RIGHT_KEY] = KEY_D;
			player->commands[BOMB_KEY] = KEY_SHIFT_LEFT;
			break;

		case BLACK_PLAYER_ID:
			player->commands[WALK_UP_KEY] = KEY_ARROW_UP;
			player->commands[WALK_DOWN_KEY] = KEY_ARROW_DOWN;
			player->commands[WALK_LEFT_KEY] = KEY_ARROW_LEFT;
			player->commands[WALK_RIGHT_KEY] = KEY_ARROW_RIGHT;
			player->commands[BOMB_KEY] = KEY_RIGHT_ZERO;
			break;
	}

	return player;
}

void resetPlayer(Player* player) {
	player->frame = 0;
	player->animation = ANIMATION_WALKING_DOWN;
	player->velocity = PLAYER_INIT_VELOCITY;

	switch (player->id) {
		case WHITE_PLAYER_ID:
			player->x = TILE_SIZE + 8;
    		player->y = 3 * TILE_SIZE;
			break;

		case BLACK_PLAYER_ID:
			player->x = (MAP_WIDTH - 2) * TILE_SIZE + 8;
    		player->y = (MAP_HEIGHT - 2) * TILE_SIZE + 22;
			break;
	}
}

void deletePlayer(Player* player) {
	free(player);
}

void getCenterTileCoord(Player* player, char* tileCoord) {
    tileCoord[0] = (player->x + (PLAYER_WIDTH >> 1) - 8) >> 4;
    tileCoord[1] = (player->y + (PLAYER_HEIGHT >> 1) - 32) >> 4;
}

void getTileCoord(Player* player, char dx, char dy, char* tileCoord) {
    tileCoord[0] = (player->x + dx - 8) >> 4;
    tileCoord[1] = (player->y + dy - 32) >> 4;
}

void walk(Player* player, TiledMap* tiledMap, char dir) {
	switch (dir) {
		case DIR_UP:
			player->animation = ANIMATION_WALKING_UP;

	        if (!(getTile(tiledMap, player->x, player->y + 8 - player->velocity) & 0x1)) {
	            if (!(getTile(tiledMap, player->x + PLAYER_WIDTH - 1, player->y + 8 - player->velocity) & 0x1)) {
	                player->y -= player->velocity;
	            }

	            else {
	                player->animation = ANIMATION_WALKING_LEFT;
	                player->x -= player->velocity;
	            }
	        }

	        else if (!(getTile(tiledMap, player->x + PLAYER_WIDTH - 1, player->y + 8 - player->velocity) & 0x1)) {
                player->animation = ANIMATION_WALKING_RIGHT;
                player->x += player->velocity;
	        }

			break;

		case DIR_DOWN:
			player->animation = ANIMATION_WALKING_DOWN;

	        if (!(getTile(tiledMap, player->x, player->y + PLAYER_HEIGHT + player->velocity) & 0x1)) {
	            if (!(getTile(tiledMap, player->x + PLAYER_WIDTH - 1, player->y + PLAYER_HEIGHT + player->velocity) & 0x1))
	                player->y += player->velocity;

	            else {
	                player->animation = ANIMATION_WALKING_LEFT;
	                player->x -= player->velocity;
	            }
	        }

	        else if (!(getTile(tiledMap, player->x + PLAYER_WIDTH - 1, player->y + PLAYER_HEIGHT + player->velocity) & 0x1)) {
	            player->animation = ANIMATION_WALKING_RIGHT;
	            player->x += player->velocity;
	        }

			break;

		case DIR_RIGHT:
			player->animation = ANIMATION_WALKING_RIGHT;

	        if (!(getTile(tiledMap, player->x + PLAYER_WIDTH + player->velocity, player->y + PLAYER_HEIGHT) & 0x1)) {
	            if (!(getTile(tiledMap, player->x + PLAYER_WIDTH + player->velocity, player->y + 10) & 0x1))
	                player->x += player->velocity;

	            else {
	                player->animation = ANIMATION_WALKING_DOWN;
	                player->y += player->velocity;
	            }
	        }

	        else if (!(getTile(tiledMap, player->x + PLAYER_WIDTH + player->velocity, player->y + 10) & 0x1)) {
	            player->animation = ANIMATION_WALKING_UP;
	            player->y -= player->velocity;
	        }

			break;

		case DIR_LEFT:
			player->animation = ANIMATION_WALKING_LEFT;

	        if (!(getTile(tiledMap, player->x - player->velocity, player->y + PLAYER_HEIGHT) & 0x1)) {
	            if (!(getTile(tiledMap, player->x - player->velocity, player->y + 10) & 0x1))
	                player->x -= player->velocity;

	            else {
	                player->animation = ANIMATION_WALKING_DOWN;
	                player->y += player->velocity;
	            }
	        }

	        else if (!(getTile(tiledMap, player->x - player->velocity, player->y + 10) & 0x1)) {
	            player->animation = ANIMATION_WALKING_UP;
	            player->y -= player->velocity;
	        }

			break;
	}

	if (frames % FRAMES_PLAYER_ANIMATION_WALK == 0)
        player->frame = (player->frame + 1) % PLAYER_FRAMES;

	drawPartialTiles(player, tiledMap);
}

void drawPartialTiles(Player* player, TiledMap* tiledMap) {
    char topLeft[2];
    char botRight[2];
    getTileCoord(player, -1, -1, topLeft);
    getTileCoord(player, PLAYER_WIDTH, PLAYER_HEIGHT, botRight);

    int i, j;
    for (i = topLeft[1]; i <= botRight[1]; i++) {
    	for (j = topLeft[0]; j <= botRight[0]; j++) {
    		unsigned short int imgCoord[2];
		    getTileSpriteFrame(tiledMap, j, i, imgCoord);

		    unsigned short int dx = 0, dy = 0; 
		    drawImage((j << TILE_SIZE_SHIFT) + 8, (i << TILE_SIZE_SHIFT) + 32, imgCoord[0], imgCoord[1], TILE_SIZE, TILE_SIZE);
    	}
    }
}

void drawPlayer(Player* player, TiledMap* tiledMap) {
	//drawPartialTiles(player, tiledMap);
	drawImage(player->x, player->y, animationFrames[player->animation][player->frame], 28 * player->id, PLAYER_WIDTH, PLAYER_HEIGHT);
}
