#ifndef _spriteframes_h_
#define _spriteframes_h_

// Non animated tiles
#define SF_SOLID_TILE               0, 107
#define SF_BRICK_TILE              17, 107
#define SF_SHADOW_GRASS_TILE       34, 107
#define SF_GRASS_TILE              51, 107

// bomb tile
#define X_BOMB						68
#define Y_BOMB_0					107
#define Y_BOMB_1					124
#define Y_BOMB_2					141

#define SF_BOMB_TILE_0				X_BOMB, Y_BOMB_0
#define SF_BOMB_TILE_1				X_BOMB, Y_BOMB_1
#define SF_BOMB_TILE_2				X_BOMB, Y_BOMB_2
#define SF_BOMB_TILE_3				X_BOMB, Y_BOMB_1

// Explosion tiles
#define SF_EXPLOSION_LEFT_0			0, 216
#define SF_EXPLOSION_LEFT_1			81, 216
#define SF_EXPLOSION_LEFT_2			164, 216
#define SF_EXPLOSION_LEFT_3			249, 216
#define SF_EXPLOSION_LEFT_4			333, 216

#define SF_EXPLOSION_MID_LEFT_0		16, 216
#define SF_EXPLOSION_MID_LEFT_1		97, 216
#define SF_EXPLOSION_MID_LEFT_2		180, 216
#define SF_EXPLOSION_MID_LEFT_3		265, 216
#define SF_EXPLOSION_MID_LEFT_4		349, 216

#define SF_EXPLOSION_RIGHT_0		64, 216
#define SF_EXPLOSION_RIGHT_1		145 , 216
#define SF_EXPLOSION_RIGHT_2		228, 216
#define SF_EXPLOSION_RIGHT_3		313, 216
#define SF_EXPLOSION_RIGHT_4		397, 216

#define SF_EXPLOSION_MID_RIGHT_0	48, 216
#define SF_EXPLOSION_MID_RIGHT_1	129 , 216
#define SF_EXPLOSION_MID_RIGHT_2	212, 216
#define SF_EXPLOSION_MID_RIGHT_3	97, 216
#define SF_EXPLOSION_MID_RIGHT_4	381, 216

#define SF_EXPLOSION_TOP_0			32, 184
#define SF_EXPLOSION_TOP_1			113, 184
#define SF_EXPLOSION_TOP_2			196, 184
#define SF_EXPLOSION_TOP_3			281, 184
#define SF_EXPLOSION_TOP_4			365, 184

#define SF_EXPLOSION_MID_TOP_0		32, 200
#define SF_EXPLOSION_MID_TOP_1		113, 200
#define SF_EXPLOSION_MID_TOP_2		196, 200
#define SF_EXPLOSION_MID_TOP_3		281, 200
#define SF_EXPLOSION_MID_TOP_4		365, 200

#define SF_EXPLOSION_BOTTOM_0		32, 248
#define SF_EXPLOSION_BOTTOM_1		113, 248
#define SF_EXPLOSION_BOTTOM_2		196, 248
#define SF_EXPLOSION_BOTTOM_3		281, 248
#define SF_EXPLOSION_BOTTOM_4		365, 248

#define SF_EXPLOSION_MID_BOTTOM_0	32, 232  
#define SF_EXPLOSION_MID_BOTTOM_1	113, 232
#define SF_EXPLOSION_MID_BOTTOM_2	196, 232
#define SF_EXPLOSION_MID_BOTTOM_3	281, 232
#define SF_EXPLOSION_MID_BOTTOM_4	365, 232

#define SF_EXPLOSION_CENTER_0		32, 216
#define SF_EXPLOSION_CENTER_1		113, 216
#define SF_EXPLOSION_CENTER_2		196, 216
#define SF_EXPLOSION_CENTER_3		281, 216
#define SF_EXPLOSION_CENTER_4		365, 216

// Exploding brick
#define SF_EXPLODING_BRICK_0		0, 124
#define SF_EXPLODING_BRICK_1		17, 124
#define SF_EXPLODING_BRICK_2		0, 141
#define SF_EXPLODING_BRICK_3		17, 141
#define SF_EXPLODING_BRICK_4		0, 158
#define SF_EXPLODING_BRICK_5		17, 158

// Hud spriteframes
#define SF_WHITE_HUD_0          	0, 0, 14, 16
#define SF_BLACK_HUD_0          	0, 28, 14, 16
#define SF_BLUE_HUD_0           	0, 55, 14, 16
#define SF_RED_HUD_0            	0, 82, 14, 16

#define SF_WHITE_HUD_1         		16, 0, 14, 16
#define SF_BLACK_HUD_1         	 	16, 28, 14, 16
#define SF_BLUE_HUD_1          	 	16, 55, 14, 16
#define SF_RED_HUD_1           		16, 82, 14, 16

// Main menu sprite frames
#define LOGO_WIDTH          		222
#define LOGO_BOTTOM_HEIGHT  		79
#define LOGO_TOP_HEIGHT     		57
#define LOGO_MARGIN_TOP     		15
#define LOGO_VEL_ANIMATION  		10

#define MENU_MARGIN_BOTTOM  		20
#define MENU_HEIGHT         		38
#define MENU_WIDTH         			124

#define ARROW_WIDTH         		8
#define ARROW_HEIGHT        		12
#define ARROW_MARGIN_RIGHT  		4

#define BIG_ZEPPELIN_WIDTH 			64
#define BIG_ZEPPELIN_HEIGHT		  	41
#define BIG_ZEPPELIN_MARGIN_RIGHT 	10

#define LITTLE_ZEPPELIN_HEIGHT 		18
#define LITTLE_ZEPPELIN_WIDTH 		31

#define SF_BACKGROUND				422, 51, 320, 116
#define SF_BALOON					244, 107, 42, 76
#define SF_LITTLE_ZEPPELIN			510, 29, LITTLE_ZEPPELIN_WIDTH, LITTLE_ZEPPELIN_HEIGHT
#define SF_BIG_ZEPPELIN				542, 0, BIG_ZEPPELIN_WIDTH, BIG_ZEPPELIN_HEIGHT
#define SF_LOGO_BOTTOM				421, 225, LOGO_WIDTH, LOGO_BOTTOM_HEIGHT
#define SF_LOGO_TOP					421, 168, LOGO_WIDTH, LOGO_TOP_HEIGHT
#define SF_ARROW					510, 17, ARROW_WIDTH, ARROW_HEIGHT
#define SF_MENU						0, 266, MENU_WIDTH, MENU_HEIGHT

// Player X Sprite Frame
#define SF_WALKING_DOWN_0			67
#define SF_WALKING_DOWN_1			49
#define SF_WALKING_DOWN_2			67
#define SF_WALKING_DOWN_3			85

#define SF_WALKING_LEFT_0			122
#define SF_WALKING_LEFT_1			103
#define SF_WALKING_LEFT_2			122
#define SF_WALKING_LEFT_3			140

#define SF_WALKING_RIGHT_0			177
#define SF_WALKING_RIGHT_1			158
#define SF_WALKING_RIGHT_2			177
#define SF_WALKING_RIGHT_3			195

#define SF_WALKING_UP_0				234
#define SF_WALKING_UP_1				216
#define SF_WALKING_UP_2				234
#define SF_WALKING_UP_3				252

#define SF_WALKING_DYING_0			341
#define SF_WALKING_DYING_1			358
#define SF_WALKING_DYING_2			375
#define SF_WALKING_DYING_3			392

// Numbers
#define X_NUMBER_0					441
#define X_NUMBER_1					450
#define X_NUMBER_2					459
#define X_NUMBER_3					468
#define X_NUMBER_4					477
#define X_NUMBER_5					486
#define X_NUMBER_6					495
#define X_NUMBER_7					504
#define X_NUMBER_8					513
#define X_NUMBER_9					522
#define X_COLON						416

#define Y_NUMBERS 					2
#define NUMBERS_WIDTH				8
#define NUMBERS_HEIGHT				14

#define SF_NUMBER_0                 X_NUMBER_0, Y_NUMBERS, NUMBERS_WIDTH, NUMBERS_HEIGHT
#define SF_NUMBER_1                 X_NUMBER_1, Y_NUMBERS, NUMBERS_WIDTH, NUMBERS_HEIGHT
#define SF_NUMBER_2                 X_NUMBER_2, Y_NUMBERS, NUMBERS_WIDTH, NUMBERS_HEIGHT
#define SF_NUMBER_3                 X_NUMBER_3, Y_NUMBERS, NUMBERS_WIDTH, NUMBERS_HEIGHT
#define SF_NUMBER_4                 X_NUMBER_4, Y_NUMBERS, NUMBERS_WIDTH, NUMBERS_HEIGHT
#define SF_NUMBER_5                 X_NUMBER_5, Y_NUMBERS, NUMBERS_WIDTH, NUMBERS_HEIGHT
#define SF_NUMBER_6                 X_NUMBER_6, Y_NUMBERS, NUMBERS_WIDTH, NUMBERS_HEIGHT
#define SF_NUMBER_7                 X_NUMBER_7, Y_NUMBERS, NUMBERS_WIDTH, NUMBERS_HEIGHT
#define SF_NUMBER_8                 X_NUMBER_8, Y_NUMBERS, NUMBERS_WIDTH, NUMBERS_HEIGHT
#define SF_NUMBER_9                 X_NUMBER_9, Y_NUMBERS, NUMBERS_WIDTH, NUMBERS_HEIGHT
#define SF_COLON                    X_COLON, Y_NUMBERS, NUMBERS_WIDTH, NUMBERS_HEIGHT

#endif
