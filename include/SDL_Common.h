#ifndef SDL_CONTEXT_H
#define SDL_CONTEXT_H


#include <memory>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

namespace game {
    constexpr int g_logicalWidth{1280};
    constexpr int g_logicalHeight{1056};
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
	int width{1920};
	int height{1080};

	Window window{};
	Renderer renderer{};
};

inline Texture loadSVGTexture(SDL_Renderer* renderer, std::string_view path, int width, int height) {
	auto* file {SDL_IOFromFile(path.data(), "rb")};
    if(!file) {
        SDL_Log("IO Failure: %s", SDL_GetError());
    }

    auto* surface {IMG_LoadSizedSVG_IO(file, width, height)};
    SDL_CloseIO(file);
    if(!surface) {
        SDL_Log("SVG Failure: %s", SDL_GetError());
    }

    Texture texture {SDL_CreateTextureFromSurface(renderer, surface)};
    SDL_DestroySurface(surface);
    if(!texture) {
        SDL_Log("Create Texture Error: %s", SDL_GetError());
    }

	return texture;
}


#endif