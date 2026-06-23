#ifndef SDL_CONTEXT_H
#define SDL_CONTEXT_H


#include <memory>

#include <SDL3/SDL.h>

namespace Config {
    constexpr static int logicalWidth{1280};
    constexpr static int logicalHeight{704};
}

// Custom Deletor struct for std::unique_ptr
struct SDL_Deleter {
	void operator()(SDL_Window *w) const {
		SDL_DestroyWindow(w);
	}
	
	void operator()(SDL_Renderer *r) const {
		SDL_DestroyRenderer(r);
	}
    
    void operator()(SDL_Texture *t) const {
        SDL_DestroyTexture(t);
    }
};

// Using Alias instead of all this nonsense
using Window    = std::unique_ptr<SDL_Window,   SDL_Deleter>;
using Renderer  = std::unique_ptr<SDL_Renderer, SDL_Deleter>;
using Texture   = std::unique_ptr<SDL_Texture,  SDL_Deleter>;

struct SDL_State {
	int width{1280};
	int height{720};

	Window window{};
	Renderer renderer{};
};


#endif