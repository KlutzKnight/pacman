#ifndef GHOST_H
#define GHOST_H


#include "Entity.h"

#include <SDL3/SDL.h>

class Ghost : public Entity {
    public:
        Ghost(Texture& mainTexture, Texture& alternateTexture)
            : Entity(mainTexture)
            , m_alternateTexture {alternateTexture}
        {
            makeFrames();
        }
        Ghost& operator=(const Ghost&) = delete;
        Ghost& operator=(Ghost&&) = default;

        void update(const double deltaTime);
        void render(SDL_Renderer *renderer) { draw(renderer); }

    private:
        struct GhostAssets {
            // The width of the sprite 
            // sheet to be loaded as texture
            static constexpr int textureWidth {384};
    	    // The height of the sprite 
            // sheet to be loaded as texture
            static constexpr int textureHeight {148};
            // The size of the sprite of the ghost to be displayed
            static constexpr float spriteWidth {textureWidth / 3};
            // The size of the sprite of the ghost to be displayed
            static constexpr float spriteHeight {textureHeight};
        };

        struct GhostAnimation {
            // The total states (orientations) of the ghost
            // Left and Right are controlled by flipping
            // Up represented by 1, Down represented by 2
            static constexpr Index frameCount {3};
        };

        void turnLeft() { setFlipMode(SDL_FLIP_NONE); }
        void turnRight() { setFlipMode(SDL_FLIP_HORIZONTAL); }
        void turnUp() { m_currentFrame = 1; }
        void turnDown() { m_currentFrame = 2; }
        void makeFrames() override;

        // Speed of the Ghost(s) in Pixels per second
        static constexpr int speed {128};

        // Frightened Texture of the ghosts
        Texture& m_alternateTexture;
        int direction{};
};


#endif