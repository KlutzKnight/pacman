#include "Ghost.h"

#include <cmath>

void Ghost::move(const double deltaTime) {
    animationTimer += deltaTime;
    double moveAmount = 500 * std::cos(deltaTime * animationTimer);

    destinationRect().x += static_cast<float> (moveAmount);
}

void Ghost::makeFrames() {
    m_frames.emplace_back(
        SDL_FRect {
            .x = 0,
            .y = 0,
            .w = spriteWidth,
            .h = spriteHeight
        }
    );
}

void Ghost::advanceFrame([[maybe_unused]] double deltaTime) {
    ;
}