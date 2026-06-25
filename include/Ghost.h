#ifndef GHOST_H
#define GHOST_H


#include "Entity.h"

class Ghost : public Entity {
    public:
        Ghost(SDL_Renderer* renderer)
            : Entity(renderer, spritePath, textureWidth, textureHeight)
        {
        }

        void move(const double deltaTime);
        void makeFrames() override;
        void advanceFrame(double deltaTime) override;
    
    private:
        static constexpr std::string_view spritePath = "assets/ghosts/ghost_g1.svg";
        // Speed of the Ghost(s) in Pixels per second
        static constexpr int speed {128};
        // Total Number of Frames in the sprite sheet
        static constexpr Index frameCount {1};
        // The width of the sprite 
        // sheet to be loaded as texture
        static constexpr int textureWidth {128 * 4};
    	// The height of the sprite 
        // sheet to be loaded as texture
        static constexpr int textureHeight {148 * 4};
        // The size of the sprite of the ghost to be displayed
        static constexpr float spriteWidth {textureWidth};
        // The size of the sprite of the ghost to be displayed
        static constexpr float spriteHeight {textureHeight};
};


#endif