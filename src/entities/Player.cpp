#include "Player.h"

#include <SDL3_image/SDL_image.h>

#include "SDL_Context.h"

Player::Player (SDL_Renderer* renderer) {
    auto* file = SDL_IOFromFile("assets/pacman/pacman.svg", "rb");
    if(!file) {
        SDL_Log("IO Failure: %s", SDL_GetError());
    }

    auto* surface {IMG_LoadSizedSVG_IO(file, s_textureWidth, s_textureHeight)};
    SDL_CloseIO(file);
    if(!surface) {
        SDL_Log("SVG Failure: %s", SDL_GetError());
    }

    m_playerTexture = Texture {SDL_CreateTextureFromSurface(renderer, surface)};
    SDL_DestroySurface(surface);
    if(!m_playerTexture) {
        SDL_Log("Create Texture Error: %s", SDL_GetError());
    }
}

void Player::move(const bool* keyboardState, const double deltaTime) {
    const float moveAmount = s_speed * static_cast<float> (deltaTime);

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