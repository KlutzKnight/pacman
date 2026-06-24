#ifndef PLAYER_H
#define PLAYER_H


#include <SDL3/SDL.h>

#include "Entity.h"

class Player : public Entity {
    public:
        Player (SDL_Renderer* renderer);
        void move(const bool* keyboardState, const double deltaTime);
        void makeFrames();
        void advanceFrame(double deltaTime);
        const SDL_FRect& currentFrame() const { return m_frames[m_currentFrame]; }

    private:
        // Speed of player in Pixels per second
        constexpr static int speed {128};
        // Total Number of Frames in the sprite sheet
        constexpr static Index frameCount {16};
        // The width and height of the sprite 
        // sheet to be loaded as texture
        constexpr static int textureWidth {2116};
    	constexpr static int textureHeight {136};
};


#endif