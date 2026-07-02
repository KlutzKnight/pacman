#ifndef MAP_H
#define MAP_H


#include <vector>
#include <unordered_map>

#include <SDL3/SDL.h>

#include "GameConfig.h"
#include "Texture.h"

class Map {
    public:
        using Index = std::vector<std::string>::size_type;
        Map(Texture& straightTexture, Texture& cornerTexture) 
            : m_mapTextureStraight {straightTexture}
            , m_mapTextureCorner {cornerTexture}
        {
        }

        void loadClassicMap();
        void draw(SDL_Renderer* renderer);
        bool isEmptyTile (Index x, Index y) const;

    private:
        enum class TileType {
            empty,
            straight,
            corner,
        };

        SDL_FRect& destination() { return m_dst; }
        SDL_Texture* texture(TileType atlasIndex);

        Texture& m_mapTextureStraight;
        Texture& m_mapTextureCorner;
        // Center the Map
        static constexpr float initialX {static_cast<float>(GameConfig::g_logicalWidth - GameConfig::g_classicMapWidth * GameConfig::g_tileSize)/2};
        static constexpr float initialY {static_cast<float>(GameConfig::g_logicalHeight - GameConfig::g_classicMapHeight * GameConfig::g_tileSize)/2};

        // Rectangle on the screen to put each tile in
        SDL_FRect m_dst {
            .x = initialX,
	    	.y = initialY,
	    	.w = static_cast<float> (GameConfig::g_tileSize),
	    	.h = static_cast<float> (GameConfig::g_tileSize),
	    };

        struct TileInfo {
            TileType atlasIndex;
            double angle;
        };

        const std::unordered_map<char, TileInfo> tileMap {
            {'-', {TileType::straight,   0}},
            {'|', {TileType::straight,  90}},
            {'F', {TileType::corner,     0}},
            {'7', {TileType::corner,    90}},
            {'L', {TileType::corner,   270}},
            {'J', {TileType::corner,   180}},
        };

        std::vector<std::string> m_asciiMap {};
};

#endif