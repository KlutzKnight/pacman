#include "Map.h"

#include <fstream>

#include <SDL3/SDL.h>

#include "GameConfig.h"

void Map::loadClassicMap() {
    std::ifstream inf{"assets/map/Map.txt"};
    if(!inf) {
        throw std::runtime_error("Uh oh, Map.txt could not be opened for reading!");
    }

    std::string line;
    while(std::getline(inf, line)) {
        m_asciiMap.push_back(line);
    }
}
void Map::makeFrames() {
    m_tiles.insert({
        TileType::topLeft,
        {48,48,16,16}
    });
    m_tiles.insert({
        TileType::topRight,
        {80,48,16,16}
    });
    m_tiles.insert({
        TileType::bottomLeft,
        {48,80,16,16}
    });
    m_tiles.insert({
        TileType::bottomRight,
        {80,80,16,16}
    });
    m_tiles.insert({
        TileType::horizontal,
        {64,48,16,16}
    });
    m_tiles.insert({
        TileType::vertical,
        {80,64,16,16}
    });
    m_tiles.insert({
        TileType::gate,
        {150,108,16,16}
    });
}
void Map::draw(SDL_Renderer* renderer) {
    size_t rows {m_asciiMap.size()};

    destination().y = initialY;
    for(size_t i{}; i < rows; i++) {
        destination().x = initialX;
        for(size_t j{}; j < m_asciiMap.at(i).size(); j++) {

            auto it = tileMap.find(m_asciiMap[i][j]);
            if(it != tileMap.end()) {
                m_tileType = tileMap.at(m_asciiMap[i][j]);
            }
            else {
                m_tileType = TileType::empty;
            }

            if(m_tileType != TileType::empty) {
                auto src_rect = sourceRect();
                auto dst_rect = destinationRect();
                SDL_RenderTexture(
                    renderer, 
                    texture(),
                    &src_rect,
                    &dst_rect
                );
            }
            destination().x += GameConfig::g_tileSize;
        }
        destination().y += GameConfig::g_tileSize;
    }
}

SDL_Texture* Map::texture() {
    if(m_tileType != TileType::empty) {
        return m_mapTexture.get();
    }
    else {
        return nullptr;
    }
}

SDL_FRect Map::destinationRect() {
    // Convert the destination from Rect to 
    // FRect for rendering and return it
    const SDL_Rect rect {m_dst};
    SDL_FRect frect;
    SDL_RectToFRect(&rect, &frect);
    return frect;
}
SDL_FRect Map::sourceRect() {
    // Convert the source from Rect to 
    // FRect for rendering and return it
    const SDL_Rect rect {m_tiles.at(m_tileType)};
    SDL_FRect frect;
    SDL_RectToFRect(&rect, &frect);
    return frect;
}

bool Map::isWalkable(int x, int y) const {
    if(x < 0 || y < 0) {
        return false;
    }
    
    if(y >= static_cast<int>(m_asciiMap.size()))
        return false;
    Index hz = static_cast<Index>(y);

    if(x >= static_cast<int>(m_asciiMap.at(hz).size()))
        return false;
    Index v = static_cast<Index>(x);
    
    auto tile {m_asciiMap.at(hz).at(v)};
    return  tile == '.' || // Dot
            tile == ' ' || // Empty Space
            tile == '*' || // Power Pellet
            tile == 'P' || // Player Spawn
            tile == 'G';   // Ghost House
}
bool Map::isGivenTile(int x, int y, char tile) {
    if(x < 0 || y < 0) {
        return false;
    }
    
    if(y >= static_cast<int>(m_asciiMap.size()))
        return false;
    Index hz = static_cast<Index>(y);

    if(x >= static_cast<int>(m_asciiMap.at(hz).size()))
        return false;
    Index v = static_cast<Index>(x);

    auto actualTile {m_asciiMap.at(hz).at(v)};
    return actualTile == tile;
}