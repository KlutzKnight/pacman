#ifndef WINDOW_H
#define WINDOW_H


#include <memory>
#include <stdexcept>

#include <SDL3/SDL.h>

#include "GameConfig.h"

class Window {
    public:
        struct Config {
            int width {GameConfig::g_defaultWidth};
            int height {GameConfig::g_defaultHeight};
            SDL_WindowFlags flags {SDL_WINDOW_RESIZABLE};
        };

        Window(const char *title, Config cfg = {
            .width = GameConfig::g_defaultWidth,
            .height = GameConfig::g_defaultHeight,
            .flags = SDL_WINDOW_RESIZABLE
        })
        : m_window {SDL_CreateWindow(title, cfg.width, cfg.height, cfg.flags)}
        {
            if(!m_window) {
                throw std::runtime_error(SDL_GetError());
            }
        }

        SDL_Window* get() const noexcept { return m_window.get(); }

    private:
        // Custom Deleter struct for std::unique_ptr
        struct WindowDeleter {
        	void operator()(SDL_Window *w) const noexcept {
        		SDL_DestroyWindow(w);
        	}
        };

        std::unique_ptr<SDL_Window, WindowDeleter> m_window {};
};


#endif