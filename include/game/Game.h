#ifndef GAME_H
#define GAME_H

#include <array>

#include "AssetManager.h"
#include "Ghost.h"
#include "Map.h"
#include "Navigation.h"
#include "Player.h"
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

    private:
        bool checkCollision(const Entity& first, const Entity& second);
        bool checkCollision(const Entity& entity, const Map& map);
        void update(double deltaTime);
        void render();

        SDLContext m_sdl;
        Window m_window;
        Renderer m_renderer;
        AssetManager m_assets;
        Player m_player;
        std::array<Ghost, 4> m_ghosts;
        Map m_map;
        Graph m_graph;

        const bool* m_keyboardState {SDL_GetKeyboardState(nullptr)};
        // To Calculate deltaTime
        const Uint64 m_perfCountFrequency {SDL_GetPerformanceFrequency()};
	    Uint64 m_previousTime {SDL_GetPerformanceCounter()};
};


#endif