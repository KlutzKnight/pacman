#ifndef GHOST_H
#define GHOST_H


#include "Entity.h"

#include <SDL3/SDL.h>

class Ghost : public Entity {
    public:
        Ghost(SDL_Renderer* renderer)
            : Entity(renderer, baseSpritePath, textureWidth, textureHeight)
        {
            makeFrames();
        }

        void update(const double deltaTime);
        void render(SDL_Renderer *renderer) { draw(renderer); }

    private:
        void turnLeft() { setFlipMode(SDL_FLIP_NONE); }
        void turnRight() { setFlipMode(SDL_FLIP_HORIZONTAL); }
        void turnUp() { m_currentFrame = 1; }
        void turnDown() { m_currentFrame = 2; }
        void makeFrames() override;

        static constexpr std::string_view baseSpritePath = "assets/ghosts/inky.svg";
        // Speed of the Ghost(s) in Pixels per second
        static constexpr int speed {128};
        // The width of the sprite 
        // sheet to be loaded as texture
        static constexpr int textureWidth {384};
    	// The height of the sprite 
        // sheet to be loaded as texture
        static constexpr int textureHeight {148};
        // The size of the sprite of the ghost to be displayed
        static constexpr float spriteWidth {128};
        // The size of the sprite of the ghost to be displayed
        static constexpr float spriteHeight {148};
        // The total states (orientations) of the ghost
        // Left and Right are controlled by flipping
        // Up represented by 1, Down represented by 2
        static constexpr Index frameCount {3};

        int direction{};
};


#endif