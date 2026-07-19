#include "Player.h"

void Player::makeFrames() {
    // Initializes m_frames to contain all the "frames",
    // i.e. the SDL_FRect coordinates to the 
    // sprite sheet.
    for(Index i{}; i < frameCount; i++) {
        addFrame(
            SDL_FRect {
                .x = g_spriteSize * static_cast<float>(i),
                .y = 0,
                .w = g_spriteSize,
                .h = g_spriteSize
            }
        );    
    }
}

bool Player::move(const bool* keyboardState, const double deltaTime) {
    float moveAmount = speed * static_cast<float> (deltaTime);
    m_moveAmountX = 0;
    m_moveAmountY = 0;

    // Move player based on the key pressed
    if(keyboardState[SDL_SCANCODE_W]) {
        m_currentDirection = Direction::up;
        turnUp();
        m_moveAmountY -= moveAmount;
        destination().y += m_moveAmountY;
    } else if(keyboardState[SDL_SCANCODE_S]) {
        m_currentDirection = Direction::down;
        turnDown();
        m_moveAmountY += moveAmount;
        destination().y += m_moveAmountY;
    } else if(keyboardState[SDL_SCANCODE_A]) {
        m_currentDirection = Direction::left;
        turnLeft();
        m_moveAmountX -= moveAmount;
        destination().x += m_moveAmountX;
    } else if(keyboardState[SDL_SCANCODE_D]) {
        m_currentDirection = Direction::right;
        turnRight();
        m_moveAmountX += moveAmount;
        destination().x += m_moveAmountX;
    } else {
        return false;
    }
    
    return true;
}

void Player::turnLeft() {
    setFlipMode(SDL_FLIP_HORIZONTAL);
    setAngle(0);
}

void Player::turnRight() {
    setFlipMode(SDL_FLIP_NONE);
    setAngle(0);
}

void Player::turnUp() {
    setFlipMode(SDL_FLIP_NONE);
    setAngle(-90);
}

void Player::turnDown() {
    setFlipMode(SDL_FLIP_NONE);
    setAngle(90);
}

void Player::update(const bool* keyboardState, const double deltaTime) {
    // Moves the player and updates the animation
    // frame if the player moved
    if(!move(keyboardState, deltaTime)) {
        resetFrame();
        return;
    }

    advanceFrame(deltaTime);
}

void Player::kill() {
    // Resets the position back to the initial spawn point
    destination().x = initialX;
    destination().y = initialY;
}