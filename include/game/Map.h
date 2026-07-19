#ifndef MAP_H
#define MAP_H


#include <vector>
#include <unordered_map>

#include <SDL3/SDL.h>

#include "AssetManager.h"
#include "GameConfig.h"
#include "Texture.h"

class Map {
    public:
        struct Point {
            int x;
            int y;

            bool operator==(const Point&) const = default;
        };
        using Index = std::vector<std::string>::size_type;
        Map(const AssetManager& assets)
            : m_mapTexture {assets.getTexture("Map")}
        {
            loadClassicMap();
            make_frames();
        }

        void draw(SDL_Renderer* renderer);
        bool isWalkable (int x, int y) const;

    private:
        enum class TileType {
            empty,
            horizontal,
            vertical,
            topLeft,
            topRight,
            bottomLeft,
            bottomRight
        };
        // Center the Map
        static constexpr int initialX {
            (GameConfig::g_logicalWidth - GameConfig::g_classicMapWidth * GameConfig::g_tileSize)/2
        };
        static constexpr int initialY {
            (GameConfig::g_logicalHeight - GameConfig::g_classicMapHeight * GameConfig::g_tileSize)/2
        };

        void loadClassicMap();
        SDL_Rect& destination() { return m_dst; }
        SDL_FRect destinationRect();
        SDL_FRect sourceRect();
        void make_frames();
        SDL_Texture* texture();

        const Texture& m_mapTexture;
        TileType m_tileType {};
        std::unordered_map<TileType, SDL_Rect> m_tiles;
        std::vector<std::string> m_asciiMap {};

        const std::unordered_map<char, TileType> tileMap {
            {'-', TileType::horizontal},
            {'|', TileType::vertical},
            {'F', TileType::topLeft},
            {'7', TileType::topRight},
            {'L', TileType::bottomLeft},
            {'J', TileType::bottomRight},
        };


        // Rectangle on the screen to put each tile in
        SDL_Rect m_dst {
            .x = initialX,
	    	.y = initialY,
	    	.w = GameConfig::g_tileSize,
	    	.h = GameConfig::g_tileSize,
	    };
};


#endif