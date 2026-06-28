#ifndef ENTITY_H
#define ENTITY_H


#include <vector>

#include <SDL3/SDL.h>

#include "Texture.h"

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
        Entity(Texture& texture)
            : m_entityTexture {texture}
        {
        }
        virtual ~Entity() = default;

    protected:
        using Index = std::vector<SDL_FRect>::size_type;

        SDL_Texture* texture() const { return m_entityTexture.get(); }
        void draw(SDL_Renderer* renderer, double angle = 0.0);
        const SDL_FRect& currentFrame() const { return m_frames[m_currentFrame]; }
        virtual void makeFrames() = 0;

        const SDL_FRect& destinationRect() const { return m_dst; }
        SDL_FRect& destination() { return m_dst; }
        SDL_FlipMode flipMode() const { return m_flag; }
        void setFlipMode(SDL_FlipMode mode) { m_flag = mode; }
        void addFrame(SDL_FRect&& frame) { m_frames.emplace_back(frame); }
        
        // All rendered entites in 32x32 space
        static constexpr float entitySize {32.0f};
        // Index of the current frame of the texture
        Index m_currentFrame {};
        
    private:
        Texture& m_entityTexture;
        // Store the different frames of the Entity
        std::vector<SDL_FRect> m_frames {};
        // Horizontal/Vertical FlipMode
        SDL_FlipMode m_flag{};
        // Rectangle on the screen to put the Entity in
        SDL_FRect m_dst {
            .x = 0,
            .y = 0,
            .w = entitySize,
            .h = entitySize,
        };
};


#endif