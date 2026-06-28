#ifndef PLAYER_H
#define PLAYER_H


#include <SDL3/SDL.h>

#include "Entity.h"

class Player : public Entity {
    public:
        Player (Texture& texture) 
            : Entity(texture)
        {
            destination().x = (1280.0f - entitySize)/2;
	    	destination().y = (1056.0f - entitySize)/2;

            makeFrames();
        }

        void update(const bool* keyboardState, const double deltaTime);
        void render(SDL_Renderer *renderer) { draw(renderer, angle()); }
        
    private:
        struct PlayerAssets {
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
        };

        struct PlayerAnimation {
            // FPS of the animation of player
            static constexpr double targetFPS {120.0};
            // Total Number of Frames in the sprite sheet
            static constexpr Index frameCount {16};
        };

        void makeFrames() override;
        double angle() const { return m_angle; }
        void setAngle(double angle) { m_angle = angle; }
        bool move(const bool* keyboardState, const double deltaTime);
        void advanceFrame(double deltaTime);

        // Speed of player in Pixels per second
        static constexpr int speed {128};

        double animationTimer {};
        // Rotation angle in degrees
        double m_angle{};
};


#endif