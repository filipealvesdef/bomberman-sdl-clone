#include "playingScene.h"
#include "tiledMap.h"
#include "player.h"

extern char clock_timer[4];
extern char lives[4];

static unsigned short int clockTimerFrames[10] = {
    X_NUMBER_0, X_NUMBER_1, X_NUMBER_2, X_NUMBER_3,
    X_NUMBER_4, X_NUMBER_5, X_NUMBER_6, X_NUMBER_7,
    X_NUMBER_8, X_NUMBER_9
};

Scene* createPlayingScene() {
    Scene* playingScene = createScene(&update, &draw);

    // scoreboard
    fillRect(0, 0, WIDTH, 31, 0xf400);
    fillRect(0, 31, WIDTH, 1, 0x9080);

    // vertical gray borders
    fillRect(0, 40, 8, 200, 0x6B4D);
    fillRect(WIDTH - 8, 40, 8, 200, 0x6B4D);

    // orange top border
    fillRect(0, 0, WIDTH, 39, 0xf400);
    fillRect(0, 39, WIDTH, 1, 0x9080);

    // hud and clock
    drawImage(57, 16, SF_WHITE_HUD_0);
    drawImage(72, 17, SF_NUMBER_0);

    drawImage(105, 16, SF_BLACK_HUD_0);
    drawImage(120, 17, SF_NUMBER_0);

    drawImage(193, 16, SF_BLUE_HUD_0);
    drawImage(208, 17, SF_NUMBER_0);

    drawImage(241, 16, SF_RED_HUD_0);
    drawImage(256, 17, SF_NUMBER_0);

    drawImage(152, 17, SF_COLON);

    initClockTimer(0, 3, 0, 0);
    // 3 vidas cada player

    TiledMap* tiledMap = initTiledmap();

    Player* whitePlayer = createPlayer(WHITE_PLAYER_ID);
    Player* blackPlayer = createPlayer(BLACK_PLAYER_ID);

    addChild(playingScene, whitePlayer);
    addChild(playingScene, blackPlayer);

    // Last node must be the tiled map
    addChild(playingScene, tiledMap);

    return playingScene;
}

void resetPlayingScene(Scene* scene) {
    TiledMap* tiledMap = (TiledMap*) getData(scene->nodes, scene->nodes->size - 1);
    free(tiledMap);

    tiledMap = initTiledmap();

    int i;
    for (i = 0; i < scene->nodes->size - 1; i++) {
        Player* player = (Player*) getData(scene->nodes, i);
        resetPlayer(player);
    }
}

static void update(Scene* scene) {

    TiledMap* tiledMap = (TiledMap*) getData(scene->nodes, scene->nodes->size - 1);

    int i;
    for (i = 0; i < scene->nodes->size - 1; i++) {
        Player* player = (Player*) getData(scene->nodes, i);

        if (player->animation == ANIMATION_DYING) {
            if (player->frame + 1 < PLAYER_FRAMES && (frames % FRAMES_PLAYER_ANIMATION_DYING) == 0)
                player->frame++;

            else if (frames % FRAMES_DELAY_REALIVEPLAYER == 0) {
                resetPlayingScene(scene);
            }
        }

        else {
            if (keys[player->commands[WALK_UP_KEY]])
                walk(player, tiledMap, DIR_UP);

            else if (keys[player->commands[WALK_DOWN_KEY]])
                walk(player, tiledMap, DIR_DOWN);

            else if(keys[player->commands[WALK_LEFT_KEY]])
                walk(player, tiledMap, DIR_LEFT);

            else if (keys[player->commands[WALK_RIGHT_KEY]])
                walk(player, tiledMap, DIR_RIGHT);

            else if (player->frame != 0) {
                player->frame = 0;
                drawPartialTiles(player, tiledMap);
            }

            if (keys[player->commands[BOMB_KEY]]) {
                char tileCoord[2];

                getCenterTileCoord(player, tileCoord);
                createBomb(tiledMap, tileCoord[0], tileCoord[1], player->id);

                keys[KEY_SHIFT_LEFT] = 0;
            }

            if (getTile(tiledMap, player->x + (PLAYER_WIDTH >> 1), player->y + (PLAYER_HEIGHT >> 1)) == EXPLOSION_TILE) {
                player->animation = ANIMATION_DYING;
            }
        }
    }

    animateTiles(tiledMap);

    if (frames % FPS == 0)
        decrementTimer(3);
}

static void draw(Scene* scene) {
    TiledMap* tiledMap = (TiledMap*) getData(scene->nodes, scene->nodes->size - 1);

    int i;
    for (i = 0; i < scene->nodes->size - 1; i++) {
        Player* player = (Player*) getData(scene->nodes, i);
        drawPlayer(player, tiledMap);
    }
}

void initClockTimer(char a, char b, char c, char d) {
    clock_timer[0] = a;
    clock_timer[1] = b;
    clock_timer[2] = c;
    clock_timer[3] = d;

    int i;
    for (i = 0; i < 4; i++)
        drawClockTimer(i, clock_timer[i]);
}

void decrementTimer(int pos) {
    clock_timer[pos]--;

    if (clock_timer[pos] < 0) {
        if (pos == 0) {
            //initMainMenuScene();
            return;
        }

        else if (pos % 2 == 0)
            clock_timer[pos] = 5;

        else
            clock_timer[pos] = 9;

        decrementTimer(pos - 1);
    }

    drawClockTimer(pos, clock_timer[pos]);
}

void drawClockTimer(int pos, char number) {
    pos > 1 ? pos++ : pos;
    drawImage(136 + (pos << 3), 17, clockTimerFrames[number], Y_NUMBERS, NUMBERS_WIDTH, NUMBERS_HEIGHT);
}
