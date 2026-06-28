#include "Map.h"

#include <fstream>
#include <iostream>

#include <SDL3/SDL.h>

#include <GameConfig.h>

void Map::loadClassicMap() {
    std::ifstream inf{"assets/map/Map.txt"};
    if(!inf) {
        std::cerr << "Uh oh, Map.txt could not be opened for reading!\n";
        return;
    }

    std::string line;
    while(std::getline(inf, line)) {
        m_asciiMap.push_back(line);
    }
}

void Map::draw(SDL_Renderer* renderer) {
    size_t rows {m_asciiMap.size()};
    size_t columns {m_asciiMap.at(0).size()};
    TileType atlasIndex {TileType::empty};
    double angle {};

    destination().y = initialY;
    for(size_t i{}; i < rows; i++) {
        destination().x = initialX;
        for(size_t j{}; j < columns; j++) {
            
            auto it = tileMap.find(m_asciiMap[i][j]);
            if(it != tileMap.end()) {
                atlasIndex = it->second.atlasIndex;
                angle = it->second.angle;
            }
            else {
                atlasIndex = TileType::empty;
                angle = 0;
            }


            SDL_RenderTextureRotated(
		    	renderer, 
		    	texture(atlasIndex),
		    	nullptr,
		    	&destination(),
		    	angle,
		    	nullptr,
		    	SDL_FLIP_NONE
		    );

            destination().x += static_cast<float> (GameConfig::g_tileSize);
        }
        destination().y += static_cast<float> (GameConfig::g_tileSize);
    }
}

SDL_Texture* Map::texture(TileType atlasIndex) {
    if(atlasIndex == TileType::straight)
        return m_mapTextureStraight.get();
    else if (atlasIndex == TileType::corner)
        return m_mapTextureCorner.get();
    else 
        return nullptr;
}