#ifndef ENTITY_H
#define ENTITY_H


#include <vector>

#include <SDL3/SDL.h>

#include "GameConfig.h"
#include "Texture.h"

class Entity {
    public:
        enum class Direction {
            left,
            right,
            up,
            down
        };
        Entity(const Texture& texture)
            : m_entityTexture {texture}
        {
        }

        virtual ~Entity() = default;
        const SDL_Rect collisionBox() const;
        constexpr int size() { return g_entitySize; }
        int centerX() const { return collisionBox().x + collisionBox().w/2; }
        int centerY() const { return collisionBox().y + collisionBox().h/2; }
        const Direction& direction() const { return m_currentDirection; }
        void stop();

    protected:
        using Index = std::vector<SDL_FRect>::size_type;

        SDL_Texture* texture() const { return m_entityTexture.get(); }
        void draw(SDL_Texture* texture, SDL_Renderer* renderer, double angle = 0.0);
        const SDL_FRect& currentFrame() const { return m_frames[m_currentFrame]; }
        void addFrame(SDL_FRect&& frame) { m_frames.emplace_back(frame); }
        virtual void advanceFrame(double deltaTime);
        virtual void makeFrames() = 0;

        const SDL_FRect& destinationRect() const { return m_dst; }
        SDL_FRect& destination() { return m_dst; }
        SDL_FlipMode flipMode() const { return m_flag; }
        void setFlipMode(SDL_FlipMode mode) { m_flag = mode; }

        // FPS of the animation of player
        static constexpr double targetFPS {30.0};
        // Total Number of Frames in the sprite sheet
        static constexpr Index frameCount {4};
        // All rendered entites in 32x32 space
        static constexpr int g_entitySize {42};
        // The size of the sprite
        static constexpr int g_spriteSize {32};
        // Index of the current frame of the texture
        Index m_currentFrame {};
        // The amount of X movement done in pixels per frame 
        float m_moveAmountX {};
        // The amount of Y movement done in pixels per frame 
        float m_moveAmountY {};
        double m_animationTimer {};
        Direction m_currentDirection {};

    private:
        const Texture& m_entityTexture;
        // Store the different frames of the Entity
        std::vector<SDL_FRect> m_frames {};
        // Horizontal/Vertical FlipMode
        SDL_FlipMode m_flag{};
        // Rectangle on the screen to put the Entity in
        SDL_FRect m_dst {
            .x = static_cast<float> (GameConfig::g_logicalWidth - size())/2.0f,
            .y = static_cast<float> (GameConfig::g_logicalHeight - size())/2.0f,
            .w = static_cast<float> (size()),
            .h = static_cast<float> (size()),
        };
};


#endif