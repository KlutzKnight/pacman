#include "AssetManager.h"

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "Texture.h"

namespace {
    constexpr AssetManager::AssetInfo player {
        .path = "assets/pacman/pacman.svg",
        .width = 2116,
        .height = 136
    };
    constexpr AssetManager::AssetInfo blinky {
        .path = "assets/ghosts/blinky.svg",
        .width = 384,
        .height = 148
    };
    constexpr AssetManager::AssetInfo clyde {
        .path = "assets/ghosts/clyde.svg",
        .width = 384,
        .height = 148
    };
    constexpr AssetManager::AssetInfo inky {
        .path = "assets/ghosts/inky.svg",
        .width = 384,
        .height = 148
    };
    constexpr AssetManager::AssetInfo pinky {
        .path = "assets/ghosts/pinky.svg",
        .width = 384,
        .height = 148
    };
    constexpr AssetManager::AssetInfo blueGhost {
        .path = "assets/ghosts/blue_ghost.svg",
        .width = 384,
        .height = 148
    };
    constexpr AssetManager::AssetInfo mapStraight {
        .path = "assets/map/map_piece_horizontal.svg",
        .width = 32,
        .height = 32
    };
    constexpr AssetManager::AssetInfo mapCorner {
        .path = "assets/map/map_piece_corner.svg",
        .width = 32,
        .height = 32
    };
}

AssetManager::AssetManager(SDL_Renderer* renderer) {
    loadSVGTexture("Player", renderer, player);
    loadSVGTexture("Blinky", renderer, blinky);
    loadSVGTexture("Clyde", renderer, blinky);
    loadSVGTexture("Inky", renderer, blinky);
    loadSVGTexture("Pinky", renderer, blinky);
    loadSVGTexture("Blue Ghost", renderer, blinky);
    loadSVGTexture("Map Straight", renderer, mapStraight);
    loadSVGTexture("Map Corner", renderer, mapCorner);
}

void AssetManager::loadSVGTexture(const std::string& key, SDL_Renderer* renderer, AssetInfo ass) {
	File file {SDL_IOFromFile(ass.path.data(), "rb")};
    if(!file) {
        throw std::runtime_error(SDL_GetError());
    }

    Surface surface {IMG_LoadSizedSVG_IO(file.get(), ass.width, ass.height)};
    if(!surface) {
        throw std::runtime_error(SDL_GetError());
    }

    Texture texture {renderer, surface.get()};
    if(!texture.get()) {
        throw std::runtime_error(SDL_GetError());
    }

    if(m_textures.contains(key)) {
        throw std::runtime_error("Texture already loaded: " + key);
    }

    m_textures.try_emplace(key, std::move(texture));
}
