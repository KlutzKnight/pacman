#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H


#include <memory>
#include <unordered_map>

#include <SDL3/SDL.h>

#include "Texture.h"

class AssetManager {
    public:
        struct AssetInfo {
            std::string_view path;
            int width;
            int height;
        };
        // Loads all the assets
        AssetManager(SDL_Renderer* renderer);
        void loadSVGTexture(const std::string& key, SDL_Renderer* renderer, AssetInfo ass);
        Texture& getTexture(std::string key) { return m_textures.at(key); }

    private:
        struct CustomDeleter {
            void operator() (SDL_IOStream* io) const noexcept {
                SDL_CloseIO(io);
            }
            void operator() (SDL_Surface* s) const noexcept {
                SDL_DestroySurface(s);
            }
        };
        using File = std::unique_ptr<SDL_IOStream, CustomDeleter>;
        using Surface = std::unique_ptr<SDL_Surface, CustomDeleter>;

        std::unordered_map<std::string, Texture> m_textures;
};


#endif