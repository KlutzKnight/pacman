#include "Ghost.h"

void Ghost::makeFrames() {
    for(Index i{}; i < frameCount; i++) {
        m_frames.emplace_back(
            SDL_FRect {
                .x = spriteWidth * static_cast<float> (i),
                .y = 0,
                .w = spriteWidth,
                .h = spriteHeight
            }
        );
    }
}

void Ghost::move(const double deltaTime) {
    const float moveAmount = speed * static_cast<float> (deltaTime);

    destination().x += moveAmount * static_cast<float> (direction);
    if(destination().x < 0) {
        direction = 1;
        turnDown();
    }
    else if(destination().x > 250) {
        direction = -1;
        turnUp();
    }

    // destination().y += moveAmount * static_cast<float> (direction);
    // if(destination().y < 0) {
    //     direction = 1;
    //     turnDown();
    // }
    // else if(destination().y > 250) {
    //     direction = -1;
    //     turnUp();
    // }
}