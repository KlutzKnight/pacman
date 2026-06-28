#ifndef SDL_CONTEXT_H
#define SDL_CONTEXT_H


#include <memory>
#include <stdexcept>

#include <SDL3/SDL.h>

class SDLContext {
    public:
        SDLContext() {
            if(!SDL_Init(SDL_INIT_VIDEO)) {
                throw std::runtime_error(SDL_GetError());
            }
        }

        ~SDLContext() {
            SDL_Quit();
        }
};


#endif