#ifndef ENTITY_H
#define ENTITY_H


#include <vector>

#include <SDL3/SDL.h>

#include "SDL_Common.h"

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
        Entity(SDL_Renderer* renderer, std::string_view path, int width, int height) {
            m_entityTexture = loadSVGTexture(renderer, path, width, height);
        }
        virtual ~Entity() = default;

        SDL_Texture* texture() const { return m_entityTexture.get(); }
        SDL_FlipMode flipMode() const { return m_flag; }
        
        const SDL_FRect& currentFrame() const { return m_frames[m_currentFrame]; }

    protected:
        using Index = std::vector<SDL_FRect>::size_type;
        
        virtual void makeFrames() = 0;
        const SDL_FRect& destinationRect() const { return m_dst; }
        SDL_FRect& destination() { return m_dst; }
        void setFlipMode(SDL_FlipMode mode) { m_flag = mode; }
        void draw(SDL_Renderer* renderer, double angle = 0.0);

        Texture m_entityTexture{};
        // The size of the rendered entity
        static constexpr float entitySize {32.0f};
        std::vector<SDL_FRect> m_frames {};
        Index m_currentFrame {};

    private:
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