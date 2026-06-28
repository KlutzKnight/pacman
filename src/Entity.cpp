#include "Entity.h"

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