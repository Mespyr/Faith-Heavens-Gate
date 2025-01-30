#include <SDL2/SDL.h>

#include <cstdint>
#include <iostream>
#include <ostream>

#include "palette.hpp"
#include "util.hpp"
#include "window/window.hpp"

int32_t main() {
    std::ostream& log = std::cerr;

    if (!init_lib(log)) exit(1);

    Palette _default(0x0e0e0e, 0x404040, 0x696969, 0x808080, 0xA9A9A9, 0xF0F0F0,
                     0x800000, 0xFF0000, 0xFF8C00, 0xFFFF00, 0xADFF2F, 0x008000,
                     0x008080, 0x00FFFF, 0x0000FF, 0x4B0082, 0x800080, 0xFF1493,
                     0xFF69B4, 0xFA8072);

    Window window(log, "Faith: Heaven's Gate", 1280, 720, _default);
    if (!window) exit(1);

    const uint64_t ticks_per_15_fps = (1000 / 15);
    uint64_t       ticks_now, ticks_last_frame = SDL_GetTicks();

    do {
        window.handle_events();
        ticks_now = SDL_GetTicks();
        if ((ticks_now - ticks_last_frame) < ticks_per_15_fps)
            SDL_Delay(1);
        else {
            window.clear();

            // a quick cross
            for (uint32_t x = 0; x < 30; x++) {
                for (uint32_t b = 0; b < 8; b++) {
                    window.set(x + 20, b + 20, Palette::ORANGE);
                }
            }
            for (uint32_t x = 0; x < 8; x++) {
                for (uint32_t b = 0; b < 44; b++) {
                    window.set(x + 31, b + 10, Palette::ORANGE);
                }
            }

            window.set(100, 99, Palette::HOT_PINK);
            window.set(101, 99, Palette::HOT_PINK);
            window.set(102, 99, Palette::HOT_PINK);
            window.set(103, 99, Palette::HOT_PINK);
            window.set(104, 99, Palette::HOT_PINK);
            window.set(105, 99, Palette::HOT_PINK);

            window.set(100, 100, Palette::HOT_PINK);
            window.set(101, 100, Palette::HOT_PINK);
            window.set(102, 100, Palette::HOT_PINK);
            window.set(103, 100, Palette::HOT_PINK);
            window.set(104, 100, Palette::HOT_PINK);
            window.set(105, 100, Palette::HOT_PINK);

            window.draw();
            ticks_last_frame = ticks_now;
        }
    } while (window);

    SDL_Quit();
    return 0;
}
