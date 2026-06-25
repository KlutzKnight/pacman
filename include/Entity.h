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
        SDL_FlipMode flipMode() const { return m_flag; }
        
        const SDL_FRect& currentFrame() const { return m_frames[m_currentFrame]; }

    protected:
        using Index = std::vector<SDL_FRect>::size_type;
        
        void setFlipMode(SDL_FlipMode mode) { m_flag = mode; }
        virtual void makeFrames() = 0;
        
        Texture m_entityTexture{};
        // The size of the rendered entity
        static constexpr float entitySize {32.0f};
        std::vector<SDL_FRect> m_frames {};
        Index m_currentFrame {};

    private:
        // Horizontal/Vertical FlipMode
        SDL_FlipMode m_flag{};
};


#endif