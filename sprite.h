#ifndef _sprite_h_
#define _sprite_h_

typedef struct sprite {
    float x;
    float y;
    unsigned short int width;
    unsigned short int height;
    unsigned short int xImage;
    unsigned short int yImage;
    char dir[2];
} Sprite;

Sprite* createSprite(float x, float y,  unsigned short int xImage, unsigned short int yImage, unsigned short int width, unsigned short int height);

#endif
