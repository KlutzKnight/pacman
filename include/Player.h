#ifndef PLAYER_H
#define PLAYER_H


#include <SDL3/SDL.h>

#include "Entity.h"

class Player : public Entity {
    public:
        Player (SDL_Renderer* renderer)
            : Entity(renderer, spriteSheetPath, textureWidth, textureHeight)
        {
        }

        void move(const bool* keyboardState, const double deltaTime);
        void makeFrames() override;
        void advanceFrame(double deltaTime) override;
        

    private:
        static constexpr std::string_view spriteSheetPath = "assets/pacman/pacman.svg";
        // The space in the sprite sheet 
        // between each subsequent sprite
        static constexpr float spriteOffset {4.0f};
        // The width of the sprite 
        // sheet to be loaded as texture
        static constexpr int textureWidth {2116};
        // The height of the sprite 
        // sheet to be loaded as texture
        static constexpr int textureHeight {136};
        // The size of the individual sprite of the player
        static constexpr float spriteSize {128.0f};
        // FPS of the animation of player
        static constexpr double targetFPS {120.0};
        // Total Number of Frames in the sprite sheet
        static constexpr Index frameCount {16};
        // Speed of player in Pixels per second
        static constexpr int speed {128};
};


#endif