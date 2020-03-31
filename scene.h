#ifndef _scene_h_
#define _scene_h_

#include "constants.h"
#include "keyCodes.h"
#include "list.h"
#include "sprite.h"

typedef struct scene {
    void (*update)(struct scene* scene);
    void (*draw)(struct scene* scene);
    List* nodes;
} Scene;

Scene* createScene(void (*updateFunc)(Scene* scene), void (*drawFunc)(Scene* scene));
void addChild(Scene* scene, void* node);
void deleteScene(Scene* scene);

extern unsigned char keys[256];
extern char pushButtons[256];
//extern char pushButtons[3];
extern char running;
extern unsigned int frames;

#endif
