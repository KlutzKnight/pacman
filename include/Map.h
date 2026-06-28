#ifndef MAP_H
#define MAP_H


#include <vector>
#include <unordered_map>

#include <SDL3/SDL.h>

#include "SDL_Common.h"

class Map {
    public:
        Map(SDL_Renderer* renderer);
        void loadClassicMap();
        void draw(SDL_Renderer* renderer);

    private:
        SDL_FRect& destination() { return m_dst; }
        SDL_Texture* texture(int a);

        Texture m_mapTextureStraight {};
        Texture m_mapTextureCorner {};
        static constexpr std::string_view classicAsciiMapPath = "assets/map/Map.txt";
        static constexpr std::string_view straightSpritePath = "assets/map/map_piece_horizontal.svg";
        static constexpr std::string_view cornerSpritePath = "assets/map/map_piece_corner.svg";
        static constexpr int tileSize {32};
        static constexpr float initialX {static_cast<float>(game::g_logicalWidth - 28*tileSize)/2};
        static constexpr float initialY {static_cast<float>(game::g_logicalHeight - 31*tileSize)/2};

        // Rectangle on the screen to put each tile in
        SDL_FRect m_dst {
            .x = initialX,
	    	.y = initialY,
	    	.w = static_cast<float> (tileSize),
	    	.h = static_cast<float> (tileSize),
	    };

        struct TileInfo {
            int atlasIndex;
            double angle;
        };

        const std::unordered_map<char, TileInfo> tileMap {
            {'-', {0,   0}},
            {'|', {0,  90}},
            {'F', {1,   0}},
            {'7', {1,  90}},
            {'L', {1, 270}},
            {'J', {1, 180}},
        };

        std::vector<std::string> m_asciiMap {};
};

#endif