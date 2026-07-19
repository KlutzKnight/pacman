#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H


#include <string_view>
#include <unordered_map>

#include "Renderer.h"
#include "Texture.h"

class AssetManager {
    public:
        struct AssetInfo {
            std::string_view key;
            std::string_view path;
        };
        // Loads all the assets
        AssetManager(Renderer& renderer);
        const Texture& getTexture(const std::string& key) const { return m_textures.at(key); }

    private:
        void loadTexture(Renderer& renderer, AssetInfo ass);
        std::unordered_map<std::string, Texture> m_textures;
};


#endif