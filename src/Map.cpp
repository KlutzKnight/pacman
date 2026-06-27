#include "Map.h"

#include <string>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

Map::Map(SDL_Renderer* renderer) {
    // Load the straight asset
    auto* file {SDL_IOFromFile(straightSpritePath.data(), "rb")};
    if(!file) {
        SDL_Log("IO Failure(Straight): %s", SDL_GetError());
    }

    auto* surface {IMG_LoadSizedSVG_IO(file, spriteSize, spriteSize)};
    SDL_CloseIO(file);
    if(!surface) {
        SDL_Log("SVG Failure(Straight): %s", SDL_GetError());
    }

    m_mapTextureStraight = Texture {SDL_CreateTextureFromSurface(renderer, surface)};
    SDL_DestroySurface(surface);
    if(!m_mapTextureStraight) {
        SDL_Log("Create Texture Error(Straight): %s", SDL_GetError());
    }

    // Load the corner asset
    file = SDL_IOFromFile(cornerSpritePath.data(), "rb");
    if(!file) {
        SDL_Log("IO Failure(Corner): %s", SDL_GetError());
    }

    surface = {IMG_LoadSizedSVG_IO(file, spriteSize, spriteSize)};
    SDL_CloseIO(file);
    if(!surface) {
        SDL_Log("SVG Failure(Corner): %s", SDL_GetError());
    }

    m_mapTextureCorner = Texture {SDL_CreateTextureFromSurface(renderer, surface)};
    SDL_DestroySurface(surface);
    if(!m_mapTextureCorner) {
        SDL_Log("Create Texture Error(Corner): %s", SDL_GetError());
    }
}

void Map::update(SDL_Renderer* renderer) {
    size_t rows {31};
    size_t columns {28};

    SDL_FRect dst {
        .x = 0,
        .y = 0,
        .w = 32.0f,
	    .h = 32.0f,
    };

    for(size_t i{}; i < rows; i++) {
        dst.x = 0.0;
        for(size_t j{}; j < columns; j++) {

            if(asciiMap[i][j] == U'┌') {
                SDL_RenderTextureRotated(
		        	renderer, 
		        	m_mapTextureCorner.get(), 
		        	nullptr,
		        	&dst,
		        	0,
		        	nullptr,
		        	SDL_FLIP_NONE
		        );
            }
            if(asciiMap[i][j] == U'─') {
                SDL_RenderTextureRotated(
		        	renderer, 
		        	m_mapTextureStraight.get(), 
		        	nullptr,
		        	&dst,
		        	0,
		        	nullptr,
		        	SDL_FLIP_NONE
		        );
            }
            if(asciiMap[i][j] == U'│') {
                SDL_RenderTextureRotated(
		        	renderer, 
		        	m_mapTextureStraight.get(), 
		        	nullptr,
		        	&dst,
		        	90,
		        	nullptr,
		        	SDL_FLIP_NONE
		        );
            }
            if(asciiMap[i][j] == U'┐') {
                SDL_RenderTextureRotated(
		        	renderer, 
		        	m_mapTextureCorner.get(), 
		        	nullptr,
		        	&dst,
		        	90,
		        	nullptr,
		        	SDL_FLIP_NONE
		        );
            }
            if(asciiMap[i][j] == U'└') {
                SDL_RenderTextureRotated(
		        	renderer, 
		        	m_mapTextureCorner.get(), 
		        	nullptr,
		        	&dst,
		        	270,
		        	nullptr,
		        	SDL_FLIP_NONE
		        );
            }
            if(asciiMap[i][j] == U'┘') {
                SDL_RenderTextureRotated(
		        	renderer, 
		        	m_mapTextureCorner.get(), 
		        	nullptr,
		        	&dst,
		        	180,
		        	nullptr,
		        	SDL_FLIP_NONE
		        );
            }


            dst.x = static_cast<float> (((int)dst.x + 32));
        }
        dst.y = static_cast<float> (((int)dst.y + 32));
    }
}