#ifndef GAME_H
#define GAME_H


#include <SDL3/SDL.h>
#include <memory>

#include "AssetManager.h"
#include "GameState.h"
#include "Renderer.h"
#include "SDLContext.h"
#include "Window.h"

class Game {
    public:
        Game();
        ~Game() = default;
        // Iterate One instance of the game loop
        void iterate(double deltaTime);
        double getDeltaTime();
        void handleEvent(SDL_Event* event);

    private:
        SDLContext m_sdl;
        Window m_window;
        Renderer m_renderer;
        AssetManager m_assets;
        std::unique_ptr<GameState> m_currentState;

        const bool* m_keyboardState {SDL_GetKeyboardState(nullptr)};
        // To Calculate deltaTime
        const Uint64 m_perfCountFrequency {SDL_GetPerformanceFrequency()};
	    Uint64 m_previousTime {SDL_GetPerformanceCounter()};

		void update(double deltaTime);
		void render();
};


#endif