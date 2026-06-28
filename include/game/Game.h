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
        void run();
        void update(double deltaTime);
        void render();

    private:
        SDLContext m_sdl;
        Window m_window;
        Renderer m_renderer;
        AssetManager m_assets;
        Player m_player;
        std::array<Ghost, 4> m_ghosts;
        Map m_map;

        const bool* m_keyboardState {SDL_GetKeyboardState(nullptr)};
};


#endif