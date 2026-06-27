#ifndef MAP_H
#define MAP_H


#include <array>
#include <string>

#include <SDL3/SDL.h>

#include "SDL_Context.h"

class Map {
    public:
        Map(SDL_Renderer* renderer);
        void update(SDL_Renderer* renderer);

    private:
        int spriteSize {32};
        Texture m_mapTextureStraight {};
        Texture m_mapTextureCorner {};
        static constexpr std::string_view straightSpritePath = "assets/map/map_piece_horizontal.svg";
        static constexpr std::string_view cornerSpritePath = "assets/map/map_piece_corner.svg";
        static constexpr std::array<std::u32string_view, 31> asciiMap {{
            U"┌────────────┐┌────────────┐",
            U"│............││............│",
            U"│.┌──┐.┌───┐.││.┌───┐.┌──┐.│",
            U"│*│  │.│   │.││.│   │.│  │*│",
            U"│.└──┘.└───┘.└┘.└───┘.└──┘.│",
            U"│..........................│",
            U"│.┌──┐.┌┐.┌──────┐.┌┐.┌──┐.│",
            U"│.└──┘.││.└──┐┌──┘.││.└──┘.│",
            U"│......││....││....││......│",
            U"└────┐.│└──┐ ││ ┌──┘│.┌────┘",
            U"     │.│┌──┘ └┘ └──┐│.│     ",
            U"     │.││          ││.│     ",
            U"     │.││ ┌──GG──┐ ││.│     ",
            U"─────┘.└┘ │      │ └┘.└─────",
            U"      .   │      │   .      ",
            U"─────┐.┌┐ │      │ ┌┐.┌─────",
            U"     │.││ └──────┘ ││.│     ",
            U"     │.││          ││.│     ",
            U"     │.││ ┌──────┐ ││.│     ",
            U"┌────┘.└┘ └──┐┌──┘ └┘.└────┐",
            U"│............││............│",
            U"│.┌──┐.┌───┐.││.┌───┐.┌──┐.│",
            U"│.└─┐│.└───┘.└┘.└───┘.│┌─┘.│",
            U"│*..││.......PP.......││..*│",
            U"└─┐.││.┌┐.┌──────┐.┌┐.││.┌─┘",
            U"┌─┘.└┘.││.└──┐┌──┘.││.└┘.└─┐",
            U"│......││....││....││......│",
            U"│.┌────┘└──┐.││.┌──┘└────┐.│",
            U"│.└────────┘.└┘.└────────┘.│",
            U"│..........................│",
            U"└──────────────────────────┘",
        }};
};

#endif