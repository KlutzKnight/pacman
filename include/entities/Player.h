#ifndef PLAYER_H
#define PLAYER_H


#include <memory>

#include <SDL3/SDL.h>

#include "Entity.h"
#include "SDL_Context.h"

class Player : public Entity {
    public:
        Player (SDL_Renderer* renderer);

        SDL_Texture* texture() const { return m_playerTexture.get(); }

        void move(const bool* keyboardState, const double deltaTime);


    private:
        enum Direction {
            stop,
            left,
            right,
            up,
            down,
        };
        constexpr static int s_textureWidth {1192};
    	constexpr static int s_textureHeight {136};
        constexpr static int s_speed {100};
        
        Texture m_playerTexture{};
        Direction m_direction{Direction::stop};
};


#endif