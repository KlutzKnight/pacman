#include "Game.h"

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

#include <iostream>
#include <stdexcept>

SDL_AppResult SDL_AppInit(void **appstate, int, char**) {
    try {
        *appstate = new Game;
        return SDL_APP_CONTINUE;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return SDL_APP_FAILURE;
    }
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    Game& game = * static_cast<Game*>(appstate);
    try {
        game.iterate(game.getDeltaTime());
        return SDL_APP_CONTINUE;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() <<"\n";
        return SDL_APP_FAILURE;
    }
}

SDL_AppResult SDL_AppEvent(void*, SDL_Event* event) {
    switch(event->type) {
        case SDL_EVENT_QUIT:
        {
            return SDL_APP_SUCCESS;
        }
        case SDL_EVENT_WINDOW_RESIZED:
        {
            break;
        }
    }
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult) {
    Game* game = static_cast<Game*>(appstate);
    delete game;
    return;
}