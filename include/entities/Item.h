#ifndef ITEM_H
#define ITEM_H


#include <unordered_map>

#include <SDL3/SDL.h>

#include "AssetManager.h"
#include "GameConfig.h"
#include "Player.h"
#include "Map.h"
#include "Texture.h"

class Item {
    public:
        enum ItemType {
            dot,
            powerPellet,
        };
        Item(AssetManager& assets, int n, ItemType item, Map& map)
            : m_maxNumItems {n}
            , m_itemType {item}
            , m_map{map}
            , m_texture {assets.getTexture("Items")}
        {
            if(m_itemType == ItemType::dot) {
                m_location = '.';
            } else if(m_itemType == ItemType::powerPellet) {
                m_location = '*';
            } else {
                m_location = 'P';
                m_timeUntilGone = 4.0;
                m_dotsUntilSpawned = 7;
            }

            makeRect();
        }
        bool update(Player& player);
        void render(SDL_Renderer* renderer);

    private:
        // Max number of item that can be present
        int m_maxNumItems {};
        // The remaining items
        int m_currentNum {};
        ItemType m_itemType {};
        Map m_map;
        const Texture& m_texture;
        std::unordered_map<ItemType, SDL_FRect> m_srcrect;
        // How many times the item tile has been visited
        int m_visited[GameConfig::g_classicMapWidth][GameConfig::g_classicMapHeight] {};
        // Location of the item in the ascii map
        char m_location {};
        // if not collected within time, will disappear
        double m_timeUntilGone {4.0};
        // Will spawn after this many dots have been eaten
        int m_dotsUntilSpawned {};
                
        void makeRect();
};


#endif