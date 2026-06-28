#include "Player.h"

void Player::makeFrames() {
    for(Index i{}; i < frameCount; i++) {
        m_frames.emplace_back(
            SDL_FRect {
                .x = spriteSize * static_cast<float>(i) + (spriteOffset * static_cast<float>(i + 1)),
                .y = spriteOffset,
                .w = spriteSize,
                .h = spriteSize
            }
        );
    }
}

bool Player::move(const bool* keyboardState, const double deltaTime) {
    bool moved {false};
    const float moveAmount = speed * static_cast<float> (deltaTime);

    // Move player based on the key pressed
    if(keyboardState[SDL_SCANCODE_W]) {
        destination().y -= moveAmount;
		setFlipMode(SDL_FLIP_NONE);
		setAngle(-90);
        moved = true;
    }
	else if(keyboardState[SDL_SCANCODE_S]) {
        destination().y += moveAmount;
		setFlipMode(SDL_FLIP_NONE);
		setAngle(90);
        moved = true;
    }
	else if(keyboardState[SDL_SCANCODE_A]) {
        destination().x -= moveAmount;
        setFlipMode(SDL_FLIP_HORIZONTAL);
        setAngle(0);
        moved = true;
    }
	else if(keyboardState[SDL_SCANCODE_D]) {
        destination().x += moveAmount;
		setFlipMode(SDL_FLIP_NONE);	
		setAngle(0);
        moved = true;
    }
    else {
        moved = false;
    }

    return moved;
}

void Player::advanceFrame(double deltaTime) {
    animationTimer += deltaTime;
    double frameTime = 1.0/targetFPS;

    while(animationTimer >= frameTime) {
        m_currentFrame++;
        m_currentFrame %= frameCount;
        animationTimer -= frameTime;
    }
}

void Player::update(const bool* keyboardState, const double deltaTime) {
    if(move(keyboardState, deltaTime)) {
        advanceFrame(deltaTime);
    }
    else {
        m_currentFrame = 0;
    }
}