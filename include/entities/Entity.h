#ifndef ENTITY_H
#define ENTITY_H


#include <SDL3/SDL.h>

#include "SDL_Context.h"

class Entity {
    public:
        const SDL_FRect& sourceRect() const { return m_src; }
        const SDL_FRect& destinationRect() const { return m_dst; }
        SDL_FRect& sourceRect() { return m_src; }
        SDL_FRect& destinationRect() { return m_dst; }
        
        SDL_FlipMode flipMode() const { return m_flag; }
        double angle() const { return m_angle; }
        void setFlipMode(SDL_FlipMode mode) { m_flag = mode; }
        void setAngle(double angle) { m_angle = angle; }


    private:
        static constexpr float s_entitySize = 32.0f;
	    static constexpr float s_offset = 4.0f;
	    static constexpr float s_spriteSize = 128.0f;


        // Rectangle on the screen
        SDL_FRect m_dst {
            .x = (static_cast<float> (Game::g_logicalWidth) - s_entitySize)/2,
	    	.y = (static_cast<float> (Game::g_logicalHeight) - s_entitySize)/2,
	    	.w = s_entitySize,
	    	.h = s_entitySize,
	    };

        // Rectangle within the sprite
        SDL_FRect m_src {
            .x = s_offset,
	    	.y = s_offset,
	    	.w = s_spriteSize,
	    	.h = s_spriteSize,
	    };

        // Horizontal/Vertical FlipMode
        SDL_FlipMode m_flag{};
        // Rotation angle in degrees
        double m_angle{};
};


#endif