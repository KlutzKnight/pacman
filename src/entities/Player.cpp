#include "Player.h"

void Player::makeFrames() {
    for(Index i{}; i < PlayerAnimation::frameCount; i++) {
        addFrame(
            SDL_FRect {
                .x = PlayerAssets::spriteSize * static_cast<float>(i) + (PlayerAssets::spriteOffset * static_cast<float>(i + 1)),
                .y = PlayerAssets::spriteOffset,
                .w = PlayerAssets::spriteSize,
                .h = PlayerAssets::spriteSize
            }
        );
    }
}

float Player::move(const bool* keyboardState, const double deltaTime) {
    float moveAmount = speed * static_cast<float> (deltaTime);

    // Move player based on the key pressed
    if(keyboardState[SDL_SCANCODE_W]) {
        destination().y -= moveAmount;
		setFlipMode(SDL_FLIP_NONE);
		setAngle(-90);
    }
	else if(keyboardState[SDL_SCANCODE_S]) {
        destination().y += moveAmount;
		setFlipMode(SDL_FLIP_NONE);
		setAngle(90);
    }
	else if(keyboardState[SDL_SCANCODE_A]) {
        destination().x -= moveAmount;
        setFlipMode(SDL_FLIP_HORIZONTAL);
        setAngle(0);
    }
	else if(keyboardState[SDL_SCANCODE_D]) {
        destination().x += moveAmount;
		setFlipMode(SDL_FLIP_NONE);	
		setAngle(0);
    }
    else {
        moveAmount = 0;
    }

    return moveAmount;
}

void Player::advanceFrame(double deltaTime) {
    animationTimer += deltaTime;
    double frameTime = 1.0/PlayerAnimation::targetFPS;

    while(animationTimer >= frameTime) {
        m_currentFrame++;
        m_currentFrame %= PlayerAnimation::frameCount;
        animationTimer = 0;
    }
}

void Player::update(const bool* keyboardState, const double deltaTime) {
    if(!move(keyboardState, deltaTime)) {
        m_currentFrame = 0;
    }

    advanceFrame(deltaTime);
}