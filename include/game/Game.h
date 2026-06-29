#ifndef GAME_H
#define GAME_H


#include <array>

#include "SDL3/SDL.h"

#include "AssetManager.h"
#include "Ghost.h"
#include "Map.h"
#include "Player.h"
#include "Renderer.h"
#include "SDLContext.h"
#include "Window.h"

class Game {
    public:
        Game();
        ~Game() = default;
        // Iterates Once
        void iterate(double deltaTime);
        double getDeltaTime();
        // void handle(SDL_Event *event);
        
    private:
        void update(double deltaTime);
        void render();
    
        SDLContext m_sdl;
        Window m_window;
        Renderer m_renderer;
        AssetManager m_assets;
        Player m_player;
        std::array<Ghost, 4> m_ghosts;
        Map m_map;

        int m_gameWidth {GameConfig::g_defaultWidth};
        int m_gameHeight {GameConfig::g_defaultHeight};
        const bool* m_keyboardState {SDL_GetKeyboardState(nullptr)};

        // To Calculate deltaTime
        const Uint64 m_perfCountFrequency {SDL_GetPerformanceFrequency()};
	    Uint64 m_previousTime {SDL_GetPerformanceCounter()};
};


#endif