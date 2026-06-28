#ifndef TEXTURE_H
#define TEXTURE_H


#include <memory>
#include <stdexcept>

#include <SDL3/SDL.h>

class Texture {
    public:
        Texture(SDL_Renderer* renderer, SDL_Surface* surface) 
            : m_texture {SDL_CreateTextureFromSurface(renderer, surface)}
        {
            if(!m_texture) {
                throw std::runtime_error(SDL_GetError());
            }
        }
        Texture(const Texture&) = delete;
        Texture(Texture&&) = default;
        Texture& operator=(const Texture&) = delete;
        Texture& operator=(Texture&&) = default;

        SDL_Texture* get() const noexcept { return m_texture.get(); }

    private:
        // Custom Deleter struct for std::unique_ptr
        struct TextureDeleter {
        	void operator()(SDL_Texture *t) const noexcept {
        		SDL_DestroyTexture(t);
        	}
        };

        std::unique_ptr<SDL_Texture, TextureDeleter> m_texture {};
};


#endif