#include "Entity.h"

#include <SDL3_image/SDL_image.h>

Entity::Entity(SDL_Renderer* renderer, std::string_view spriteSheetPath, int textureWidth, int textureHeight) {
    auto* file = SDL_IOFromFile(spriteSheetPath.data(), "rb");
    if(!file) {
        SDL_Log("IO Failure: %s", SDL_GetError());
    }

    auto* surface {IMG_LoadSizedSVG_IO(file, textureWidth, textureHeight)};
    SDL_CloseIO(file);
    if(!surface) {
        SDL_Log("SVG Failure: %s", SDL_GetError());
    }

    m_entityTexture = Texture {SDL_CreateTextureFromSurface(renderer, surface)};
    SDL_DestroySurface(surface);
    if(!m_entityTexture) {
        SDL_Log("Create Texture Error: %s", SDL_GetError());
    }
}