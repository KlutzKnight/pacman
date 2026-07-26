#include "Item.h"

#include <SDL3/SDL.h>

#include "GameConfig.h"

bool Item::update(Player& player) {
    int x {player.centerX()/GameConfig::g_tileSize};
    int y {player.centerY()/GameConfig::g_tileSize};
    
    if(m_map.isGivenTile(x, y, m_location)) {
       m_visited[x][y]++;
    }

    return m_visited[x][y] == 1;
}
void Item::render(SDL_Renderer* renderer) {
    SDL_FRect dstrect;
    for(int i{}; i < GameConfig::g_classicMapWidth; i++) {
        for(int j{}; j < GameConfig::g_classicMapHeight; j++) {
            if(!m_map.isGivenTile(i, j, m_location)) {
                continue;
            }
            if(m_visited[i][j]) {
                continue;
            }

            if(m_itemType == cherry && m_dotsUntilSpawned != 0) {
                continue;
            }

            dstrect = {
                static_cast<float>(i * GameConfig::g_tileSize),
                static_cast<float>(j * GameConfig::g_tileSize),
                GameConfig::g_tileSize,
                GameConfig::g_tileSize
            };
            
            SDL_RenderTexture(
                renderer,
                m_texture.get(),
                &m_srcrect.at(m_itemType),
                &dstrect
            );
        }
    }
}

void Item::makeRect() {
    m_srcrect.insert({
        ItemType::dot,
        {0,16,16,16}
    });
    m_srcrect.insert({
        ItemType::powerPellet,
        {16,16,16,16}
    });
    m_srcrect.insert({
        ItemType::cherry,
        {0,0,16,16}
    });
}