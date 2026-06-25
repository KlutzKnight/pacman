#include "Player.h"

void Player::move(const bool* keyboardState, const double deltaTime) {
    const float moveAmount = speed * static_cast<float> (deltaTime);

    if(keyboardState[SDL_SCANCODE_W])
        m_direction = Direction::up;
	else if(keyboardState[SDL_SCANCODE_S])
        m_direction = Direction::down;
	else if(keyboardState[SDL_SCANCODE_A])
        m_direction = Direction::left;
	else if(keyboardState[SDL_SCANCODE_D])
        m_direction = Direction::right;

    switch(m_direction) {
        case Direction::up:
        {
            destinationRect().y -= moveAmount;
		    setFlipMode(SDL_FLIP_NONE);
		    setAngle(-90);
            break;
        }
        case Direction::down:
        {
		    destinationRect().y += moveAmount;
		    setFlipMode(SDL_FLIP_NONE);
		    setAngle(90);
            break;
        }
        case Direction::left:
        {
		    destinationRect().x -= moveAmount;
		    setFlipMode(SDL_FLIP_HORIZONTAL);
		    setAngle(0);
            break;
        }
        case Direction::right:
        {
		    destinationRect().x += moveAmount;
		    setFlipMode(SDL_FLIP_NONE);	
		    setAngle(0);
            break;
        }
        default:
        {
            break;
        }
    }
}

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

void Player::advanceFrame(double deltaTime) {
    animationTimer += deltaTime;
    double frameTime = 1.0/targetFPS;

    while(animationTimer >= frameTime) {
        m_currentFrame++;
        m_currentFrame %= frameCount;
        animationTimer = 0;
    }
}