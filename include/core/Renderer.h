#ifndef RENDERER_H
#define RENDERER_H


#include <memory>
#include <stdexcept>

#include <SDL3/SDL.h>

#include "Window.h"

class Renderer {
    public:
        Renderer(Window& window, const char* name = nullptr) 
            : m_renderer {SDL_CreateRenderer(window.get(), name)}
        {
            if(!m_renderer) {
                throw std::runtime_error(SDL_GetError());
            }

            // Enable VSync (To Cap Framerate to the monitor's refresh rate)
	        if(!SDL_SetRenderVSync(m_renderer.get(), SDL_RENDERER_VSYNC_ADAPTIVE)) {
	        	throw std::runtime_error(SDL_GetError());
	        }
        }

        SDL_Renderer* get() const noexcept { return m_renderer.get(); }

    private:
        // Custom Deleter struct for std::unique_ptr
        struct RendererDeleter {
        	void operator()(SDL_Renderer *r) const noexcept {
        		SDL_DestroyRenderer(r);
        	}
        };

        std::unique_ptr<SDL_Renderer, RendererDeleter> m_renderer {};
};


#endif