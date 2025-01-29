#pragma once

#include <SDL2/SDL_pixels.h>

#include <cassert>
#include <cstdint>
#include <unordered_map>
#include <vector>

class Palette {
  public:
    enum Color {
        BLACK,
        DARK_GREY,
        GREY,
        LIGHT_GREY,
        LIGHTER_GREY,
        WHITE,
        BLOOD_RED,
        RED,
        ORANGE,
        YELLOW,
        LIME,
        GREEN,
        TEAL,
        CYAN,
        BLUE,
        INDIGO,
        PURPLE,
        HOT_PINK,
        PINK,
        SALMON,
        COLOR_COUNT,
    };

    static_assert(
        Palette::COLOR_COUNT == 20,
        "unhandled colors inside arguments of class constructor Palette().");

    Palette(uint32_t black, uint32_t dark_grey, uint32_t grey,
            uint32_t light_grey, uint32_t lighter_grey, uint32_t white,
            uint32_t blood_red, uint32_t red, uint32_t orange, uint32_t yellow,
            uint32_t lime, uint32_t green, uint32_t teal, uint32_t cyan,
            uint32_t blue, uint32_t indigo, uint32_t purple, uint32_t hot_pink,
            uint32_t pink, uint32_t salmon);

    uint32_t get(Palette::Color color);

  private:
    std::unordered_map<Palette::Color, uint32_t> colors;
};
