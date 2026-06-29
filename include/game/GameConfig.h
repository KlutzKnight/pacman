#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H


namespace GameConfig {
    static constexpr int g_tileSize {32};

    static constexpr int g_classicMapWidth {28};
    static constexpr int g_classicMapHeight {31};

    static constexpr int g_logicalWidth {(g_classicMapWidth * g_tileSize) + (12 * g_tileSize)};
    static constexpr int g_logicalHeight {(g_classicMapHeight * g_tileSize) + (2 * g_tileSize)};

    static constexpr int g_defaultWidth {1920};
    static constexpr int g_defaultHeight {1080};
}


#endif