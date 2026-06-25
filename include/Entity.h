#ifndef ENTITY_H
#define ENTITY_H


#include <vector>

#include <SDL3/SDL.h>

#include "SDL_Context.h"

class Entity {
    public:
        /* 
         * Creates an Entity at the specified renderer 
         * 
         * 
         * @param renderer: where to render the entity
         * @param path: the path to the sprite sheet of the entity (svg)
         * @param textureWidth: The width of the sprite
         * @param textureHeight: The width of the sprite
         * 
         */
        Entity(SDL_Renderer* renderer, std::string_view path, int textureWidth, int textureHeight);
        virtual ~Entity() = default;

        SDL_Texture* texture() const { return m_entityTexture.get(); }
        const SDL_FRect& destinationRect() const { return m_dst; }
        SDL_FRect& destinationRect() { return m_dst; }
        SDL_FlipMode flipMode() const { return m_flag; }
        void setFlipMode(SDL_FlipMode mode) { m_flag = mode; }
        double angle() const { return m_angle; }
        void setAngle(double angle) { m_angle = angle; }

        const SDL_FRect& currentFrame() const { return m_frames[m_currentFrame]; }
        virtual void makeFrames() = 0;
        virtual void advanceFrame(double deltaTime) = 0;

    protected:
        using Index = std::vector<SDL_FRect>::size_type;
        enum Direction {
            stop,
            left,
            right,
            up,
            down,
        };

        // The size of the rendered entity
        static constexpr float entitySize {32.0f};
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