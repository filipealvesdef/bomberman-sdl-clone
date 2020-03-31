#include "sprite.h"

Sprite* createSprite(float x, float y,  unsigned short int xImage, unsigned short int yImage, unsigned short int width, unsigned short int height) {

    Sprite* spr = (Sprite*) malloc(sizeof(Sprite));
    
    spr->x = x;
    spr->y = y;

    spr->xImage = xImage;
    spr->yImage = yImage;
    spr->width = width;
    spr->height = height;

    return spr;
}
