#include "Ghost.h"

void Ghost::makeFrames() {
    for(Index i{}; i < GhostAnimation::frameCount; i++) {
        addFrame(
            SDL_FRect {
                .x = GhostAssets::spriteWidth * static_cast<float> (i),
                .y = 0,
                .w = GhostAssets::spriteWidth,
                .h = GhostAssets::spriteHeight
            }
        );
    }
}

void Ghost::update(const double deltaTime) {
    const float moveAmount = speed * static_cast<float> (deltaTime);

    destination().x += moveAmount * static_cast<float> (direction);
    if(destination().x < 300) {
        direction = 1;
        turnRight();
    }
    else if(destination().x > 500) {
        direction = -1;
        turnLeft();
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