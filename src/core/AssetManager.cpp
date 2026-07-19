#include "AssetManager.h"

#include <unordered_map>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "Texture.h"

namespace {
    constexpr AssetManager::AssetInfo player {
        .key = "Pacman",
        .path = "assets/pacman/PacManAssets-PacMan.png"
    };
    constexpr AssetManager::AssetInfo ghost {
        .key = "Ghost",
        .path = "assets/ghosts/PacManAssets-Ghosts.png"
    };
    constexpr AssetManager::AssetInfo map {
        .key = "Map",
        .path = "assets/map/PacManAssets-Map_TileSet.png"
    };
    constexpr AssetManager::AssetInfo items {
        .key = "Items",
        .path = "assets/items/PacManAssets-Items.png"
    };
}

AssetManager::AssetManager(Renderer& renderer) {
    loadTexture(renderer, player);
    loadTexture(renderer, ghost);
    loadTexture(renderer, map);
    loadTexture(renderer, items);
}

void AssetManager::loadTexture(Renderer& renderer, AssetInfo ass) {
	auto file {SDL_IOFromFile(ass.path.data(), "rb")};
    if(!file) {
        throw std::runtime_error(SDL_GetError());
    }

    Texture texture {IMG_LoadTexture_IO(renderer.get(), file, true)};
    if(!texture.get()) {
        throw std::runtime_error(SDL_GetError());
    }

    if(ass.key == "Map") {
        SDL_SetTextureScaleMode(texture.get(), SDL_SCALEMODE_NEAREST);
    }   
    if(m_textures.contains(std::string(ass.key))) {
        throw std::runtime_error("Texture already loaded: " + std::string(ass.key));
    }

    m_textures.emplace(ass.key, std::move(texture));
}
