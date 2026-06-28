#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H


namespace GameConfig {
    static constexpr int g_tileSize {32};

    static constexpr int g_mapWidth {28};
    static constexpr int g_mapHeight {31};

    static constexpr int g_logicalWidth {(g_mapWidth * g_tileSize) + (12 * g_tileSize)};
    static constexpr int g_logicalHeight {(g_mapHeight * g_tileSize) + (2 * g_tileSize)};

    static constexpr int g_defaultWidth {1920};
    static constexpr int g_defaultHeight {1080};
}


#endif