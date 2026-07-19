#include "Game.h"
#include <SDL3/SDL_events.h>

// Use SDL3's main function callback instead of 
// implementing the main loop
#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

#include <exception>
#include <iostream>

// To perform any one time initialization
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

// One iteration of the main game loop
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

// One iteration of the main event handling logic
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    Game* game = static_cast<Game*> (appstate);

    switch(event->type) {
        case SDL_EVENT_QUIT:
        {
            return SDL_APP_SUCCESS;
        }
        case SDL_EVENT_KEY_DOWN:
        {
            game->handleEvent(event);
            break;
        }
    }
    return SDL_APP_CONTINUE;
}

// Any cleanup to be done here
void SDL_AppQuit(void *appstate, SDL_AppResult) {
    Game* game = static_cast<Game*>(appstate);
    delete game;
    return;
}