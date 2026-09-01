#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

typedef enum {

    GAME_STATE_MENU,
    GAME_STATE_INTRO,
    GAME_STATE_PLAYING,
    GAME_STATE_PAUSED,
    GAME_STATE_END,
    GAME_STATE_ERROR

} GameState;

typedef struct {

    GameState state;

} __GameManager;

#endif
