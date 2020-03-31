#ifndef _playingScene_h_
#define _playingScene_h_

#include "spriteframes.h"
#include "scene.h"

Scene* createPlayingScene();
static void update(Scene* scene);
static void draw(Scene* scene);

void resetPlayingScene();
void decrementTimer(int pos);
void initClockTimer(char a, char b, char c, char d);
void drawClockTimer(int pos, char number);

#endif
