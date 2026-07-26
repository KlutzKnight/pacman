#ifndef WORLD_STATE_H
#define WORLD_STATE_H


#include "GameState.h"

#include <array>

#include "AssetManager.h"
#include "Ghost.h"
#include "Item.h"
#include "Map.h"
#include "Navigation.h"
#include "Player.h"
#include "Renderer.h"

class WorldState : public GameState {
    public:
        // Private constructor
        WorldState(AssetManager& assets);

        // Main loop functions
        void update(double deltaTime, const bool* keyboardState) override;
        void render(Renderer& renderer) override;
        // Event Handler and state changer 
        std::unique_ptr<GameState> handleEvent(SDL_Event* event) override;
        // Collision Detection
        bool checkCollision(const Entity& first, const Entity& second);
        bool checkCollision(const Entity& entity, const Map& map);

    private:
        Player m_player;
        std::array<Ghost, 4> m_ghosts;
        Map m_map;
        Graph m_graph;
        std::array<Item, 3> m_items;
};


#endif