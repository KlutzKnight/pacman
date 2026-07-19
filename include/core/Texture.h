#ifndef TEXTURE_H
#define TEXTURE_H


#include <memory>
#include <stdexcept>

#include <SDL3/SDL.h>

class Texture {
    public:
        Texture(SDL_Texture* texture) 
            : m_texture {texture}
        {
            if(!m_texture) {
                throw std::runtime_error(SDL_GetError());
            }
        }

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