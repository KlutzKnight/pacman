#ifndef ENTITY_H
#define ENTITY_H


#include <vector>

#include <SDL3/SDL.h>

#include "SDL_Context.h"

class Entity {
    public:
        const SDL_FRect& destinationRect() const { return m_dst; }
        SDL_FRect& destinationRect() { return m_dst; }

        SDL_FlipMode flipMode() const { return m_flag; }
        double angle() const { return m_angle; }
        SDL_Texture* texture() const { return m_entityTexture.get(); }
        void setFlipMode(SDL_FlipMode mode) { m_flag = mode; }
        void setAngle(double angle) { m_angle = angle; }

    protected:
        using Index = std::vector<SDL_FRect>::size_type;
        enum Direction {
            stop,
            left,
            right,
            up,
            down,
        };
        // The space in the sprite sheet 
        // between each subsequent sprite
        static constexpr float spriteOffset = 4.0f;
        // The size of the rendered entity
        static constexpr float entitySize = 32.0f;
        // The size of the individual sprite of the entity
        static constexpr float spriteSize = 128.0f;

        double targetFPS {120.0};    // FPS of the animation of Entity
        double animationTimer {};
        Index m_currentFrame {};
        Texture m_entityTexture{};
        std::vector<SDL_FRect> m_frames {};
        Direction m_direction{Direction::stop};

    private:
        // Rectangle on the screen to put the entity in
        // Start in the middle of the screeen
        SDL_FRect m_dst {
            .x = (static_cast<float> (game::g_logicalWidth) - entitySize)/2,
	    	.y = (static_cast<float> (game::g_logicalHeight) - entitySize)/2,
	    	.w = entitySize,
	    	.h = entitySize,
	    };

        // Horizontal/Vertical FlipMode
        SDL_FlipMode m_flag{};
        // Rotation angle in degrees
        double m_angle{};
};


#endif