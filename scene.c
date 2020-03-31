#include "scene.h"
#include <stdlib.h>

Scene* createScene(void (*updateFunc)(Scene* scene), void (*drawFunc)(Scene* scene)) {

    Scene* scene = (Scene*) malloc(sizeof(Scene));
    scene->update = updateFunc;
    scene->draw = drawFunc;

    scene->nodes = createList();

    return scene;
}

void addChild(Scene* scene, void* node) {
	pushBack(scene->nodes, node);
}

void deleteScene(Scene* scene) {
	deleteList(scene->nodes);
	free(scene);
}