#include "Entity.h"

#include <SDL3/SDL.h>

void Entity::draw(SDL_Texture* texture, SDL_Renderer* renderer, double angle) {
    SDL_RenderTextureRotated(
        renderer,
        texture,
        &currentFrame(),
        &destination(),
        angle,
        nullptr,
        flipMode()
    );
}

void Entity::stop() {
    destination().x -= m_moveAmountX;
    destination().y -= m_moveAmountY;
}

const SDL_Rect Entity::collisionBox() const {
    constexpr int leeway = g_entitySize/4;
    const SDL_Rect rect = {
        .x = static_cast<int> (m_dst.x + leeway),
        .y = static_cast<int> (m_dst.y + leeway),
        .w = g_entitySize/2,
        .h = g_entitySize/2
    };
    return rect;
}

void Entity::advanceFrame(double deltaTime) {
    // Advances the animation of the entity
    m_animationTimer += deltaTime;
    double frameTime = 1.0/targetFPS;

    while(m_animationTimer >= frameTime) {
        m_currentFrame++;
        m_currentFrame %= frameCount;
        m_animationTimer = 0;
    }
}