#ifndef _tile_h_
#define _tile_h_

#define TILE_SIZE					16
#define TILE_SIZE_SHIFT				4

// bomb attributes
#define FRAMES_BOMB_ANIMATION		10
#define CYCLES_TO_EXPLODE			4
#define QNT_FRAMES_BOMB_ANIMATION	4

// explosion animation
#define FRAMES_EXPLOSION_ANIMATION		3
#define FRAMES_EXPLOSION_STATE			5
#define QNT_FRAMES_EXPLOSION_ANIMATION	45

typedef struct tile {
	unsigned char code;
	unsigned char frame;
	unsigned char cycles;
} Tile;

#endif
