#ifndef SDL_CONTEXT_H
#define SDL_CONTEXT_H


#include <memory>

#include <SDL3/SDL.h>

namespace game {
    constexpr int g_logicalWidth{1920};
    constexpr int g_logicalHeight{1080};
}

// Custom Deletor struct for std::unique_ptr
struct SDL_Deleter {
	void operator()(SDL_Window *w) const noexcept {
		SDL_DestroyWindow(w);
	}
	
	void operator()(SDL_Renderer *r) const noexcept {
		SDL_DestroyRenderer(r);
	}
    
    void operator()(SDL_Texture *t) const noexcept{
        SDL_DestroyTexture(t);
    }
};

// Using Alias instead of all this nonsense
using Window    = std::unique_ptr<SDL_Window,   SDL_Deleter>;
using Renderer  = std::unique_ptr<SDL_Renderer, SDL_Deleter>;
using Texture   = std::unique_ptr<SDL_Texture,  SDL_Deleter>;

struct SDL_State {
	int width{game::g_logicalWidth};
	int height{game::g_logicalHeight};

	Window window{};
	Renderer renderer{};
};


#endif