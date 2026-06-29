#include "AssetManager.h"

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "Texture.h"

namespace {
    constexpr AssetManager::AssetInfo player {
        .key = std::move("Player"),
        .path = "assets/pacman/pacman.svg",
        .width = 2116,
        .height = 136
    };
    constexpr AssetManager::AssetInfo blinky {
        .key = std::move("Blinky"),
        .path = "assets/ghosts/blinky.svg",
        .width = 384,
        .height = 148
    };
    constexpr AssetManager::AssetInfo clyde {
        .key = std::move("Clyde"),
        .path = "assets/ghosts/clyde.svg",
        .width = 384,
        .height = 148
    };
    constexpr AssetManager::AssetInfo inky {
        .key = std::move("Inky"),
        .path = "assets/ghosts/inky.svg",
        .width = 384,
        .height = 148
    };
    constexpr AssetManager::AssetInfo pinky {
        .key = std::move("Pinky"),
        .path = "assets/ghosts/pinky.svg",
        .width = 384,
        .height = 148
    };
    constexpr AssetManager::AssetInfo blueGhost {
        .key = std::move("Blue Ghost"),
        .path = "assets/ghosts/blue_ghost.svg",
        .width = 384,
        .height = 148
    };
    constexpr AssetManager::AssetInfo mapStraight {
        .key = std::move("Map Straight"),
        .path = "assets/map/map_piece_horizontal.svg",
        .width = 32,
        .height = 32
    };
    constexpr AssetManager::AssetInfo mapCorner {
        .key = std::move("Map Corner"),
        .path = "assets/map/map_piece_corner.svg",
        .width = 32,
        .height = 32
    };
}

AssetManager::AssetManager(SDL_Renderer* renderer) {
    loadSVGTexture(renderer, player);
    loadSVGTexture(renderer, blinky);
    loadSVGTexture(renderer, clyde);
    loadSVGTexture(renderer, inky);
    loadSVGTexture(renderer, pinky);
    loadSVGTexture(renderer, blueGhost);
    loadSVGTexture(renderer, mapStraight);
    loadSVGTexture(renderer, mapCorner);
}

void AssetManager::loadSVGTexture(SDL_Renderer* renderer, AssetInfo ass) {
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

    if(m_textures.contains(ass.key)) {
        throw std::runtime_error("Texture already loaded: " + ass.key);
    }

    m_textures.try_emplace(ass.key, std::move(texture));
}
