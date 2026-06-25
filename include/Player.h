#ifndef PLAYER_H
#define PLAYER_H


#include <SDL3/SDL.h>

#include "Entity.h"

class Player : public Entity {
    public:
        Player (SDL_Renderer* renderer) 
            : Entity(renderer, spriteSheetPath, textureWidth, textureHeight)
        {
            makeFrames();
        }

        const SDL_FRect& destinationRect() const { return m_dst; }
        double angle() const { return m_angle; }
        void update(const bool* keyboardState, const double deltaTime);

    private:
        void setAngle(double angle) { m_angle = angle; }
        void makeFrames() override;
        bool move(const bool* keyboardState, const double deltaTime);
        void advanceFrame(double deltaTime);
        SDL_FRect& destination() { return m_dst; }

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
        static constexpr float height = static_cast<float> (game::g_logicalWidth) - entitySize;

        // Rectangle on the screen to put the player in
        // Start in the middle of the screeen
        SDL_FRect m_dst {
            .x = (static_cast<float> (game::g_logicalWidth) - entitySize)/2,
	    	.y = (static_cast<float> (game::g_logicalHeight) - entitySize)/2,
	    	.w = entitySize,
	    	.h = entitySize,
	    };

        double animationTimer {};
        // Rotation angle in degrees
        double m_angle{};
};


#endif