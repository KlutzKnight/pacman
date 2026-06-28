#include "Entity.h"

#include <SDL3/SDL.h>

void Entity::draw(SDL_Renderer* renderer, double angle) {
    SDL_RenderTextureRotated(
        renderer,
        texture(),
        &currentFrame(),
        &destination(),
        angle,
        nullptr,
        flipMode()
    );
}