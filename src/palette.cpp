#include "palette.hpp"

Palette::Palette(uint32_t black, uint32_t dark_grey, uint32_t grey,
                 uint32_t light_grey, uint32_t lighter_grey, uint32_t white,
                 uint32_t blood_red, uint32_t red, uint32_t orange,
                 uint32_t yellow, uint32_t lime, uint32_t green, uint32_t teal,
                 uint32_t cyan, uint32_t blue, uint32_t indigo, uint32_t purple,
                 uint32_t hot_pink, uint32_t pink, uint32_t salmon) {
    // save colors
    static_assert(Palette::COLOR_COUNT == 20,
                  "unhandled colors inside constructor of class Palette().");
    std::vector<std::pair<Palette::Color, uint32_t>> keys = {
        {Palette::BLACK, black},
        {Palette::DARK_GREY, dark_grey},
        {Palette::GREY, grey},
        {Palette::LIGHT_GREY, light_grey},
        {Palette::LIGHTER_GREY, lighter_grey},
        {Palette::WHITE, white},
        {Palette::BLOOD_RED, blood_red},
        {Palette::RED, red},
        {Palette::ORANGE, orange},
        {Palette::YELLOW, yellow},
        {Palette::LIME, lime},
        {Palette::GREEN, green},
        {Palette::TEAL, teal},
        {Palette::CYAN, cyan},
        {Palette::BLUE, blue},
        {Palette::INDIGO, indigo},
        {Palette::PURPLE, purple},
        {Palette::HOT_PINK, hot_pink},
        {Palette::PINK, pink},
        {Palette::SALMON, salmon},
    };
    colors.insert(keys.begin(), keys.end());
}

uint32_t Palette::get(Palette::Color color) { return colors.at(color); }
