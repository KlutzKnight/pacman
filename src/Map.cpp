#include "Map.h"

#include <fstream>
#include <iostream>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "SDL_Common.h"

Map::Map(SDL_Renderer* renderer) {
    // Load the straight asset
    m_mapTextureStraight = loadSVGTexture(renderer, straightSpritePath.data(), tileSize, tileSize);

    // Load the corner asset
    m_mapTextureCorner = loadSVGTexture(renderer, cornerSpritePath.data(), tileSize, tileSize);
}

void Map::loadClassicMap() {
    std::ifstream inf{"assets/map/Map.txt"};
    if(!inf) {
        std::cerr << "Uh oh, Map.txt could not be opened for reading!\n";
    }

    std::string line;
    while(std::getline(inf, line)) {
        m_asciiMap.push_back(line);
    }
}

void Map::draw(SDL_Renderer* renderer) {
    size_t rows {m_asciiMap.size()};
    size_t columns {m_asciiMap.at(0).size()};
    int atlasIndex {};
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
                atlasIndex = -1;
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

            destination().x += static_cast<float> (tileSize);
        }
        destination().y += static_cast<float> (tileSize);
    }
}

SDL_Texture* Map::texture(int atlasIndex) {
    if(atlasIndex == 0)
        return m_mapTextureStraight.get();
    else if (atlasIndex == 1)
        return m_mapTextureCorner.get();
    else 
        return nullptr;
}