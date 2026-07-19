#ifndef PLAYER_H
#define PLAYER_H


#include <SDL3/SDL.h>

#include "AssetManager.h"
#include "Entity.h"
#include "GameConfig.h"

class Player : public Entity {
    public:
        Player (const AssetManager& assets)
            : Entity(assets.getTexture("Pacman"))
        {
	    	destination().y = initialY;
            makeFrames();
        }

        void update(const bool* keyboardState, const double deltaTime);
        void render(SDL_Renderer *renderer) { draw(texture(), renderer, angle()); }
        void kill();

    private:
        static constexpr int initialX = (GameConfig::g_logicalWidth - GameConfig::g_tileSize)/2;
        static constexpr int initialY = (GameConfig::g_logicalHeight + 15 * GameConfig::g_tileSize)/2;
        // Speed of the Entity in Pixels per second
        static constexpr int speed {128};

        void turnLeft();
        void turnRight();
        void turnUp();
        void turnDown();

        void makeFrames() override;
        void resetFrame() { m_currentFrame = 0; }
        double angle() const { return m_angle; }
        void setAngle(double angle) { m_angle = angle; }
        bool move(const bool* keyboardState, const double deltaTime);

        // Rotation angle in degrees
        double m_angle {};
};


#endif