#include "Player.h"

#include "GameConfig.h"

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
    moveAmountX = 0;
    moveAmountY = 0;
    
    // Move player based on the key pressed
    if(keyboardState[SDL_SCANCODE_W]) {
        destination().y -= moveAmount;
		setFlipMode(SDL_FLIP_NONE);
		setAngle(-90);
        moveAmountY -= moveAmount;
        
    }
	else if(keyboardState[SDL_SCANCODE_S]) {
        destination().y += moveAmount;
		setFlipMode(SDL_FLIP_NONE);
		setAngle(90);
        moveAmountY += moveAmount;
    }
	else if(keyboardState[SDL_SCANCODE_A]) {
        destination().x -= moveAmount;
        setFlipMode(SDL_FLIP_HORIZONTAL);
        setAngle(0);
        moveAmountX -= moveAmount;
    }
	else if(keyboardState[SDL_SCANCODE_D]) {
        destination().x += moveAmount;
		setFlipMode(SDL_FLIP_NONE);	
		setAngle(0);
        moveAmountX += moveAmount;
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
        resetFrame();
    }

    advanceFrame(deltaTime);
}

void Player::stop() {
    destination().x -= moveAmountX;
    destination().y -= moveAmountY;
}

void Player::kill() {
    destination().x = (GameConfig::g_logicalWidth - g_entitySize)/2;
    destination().y = (GameConfig::g_logicalHeight + 15 * g_entitySize)/2;
}