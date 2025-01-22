#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>

#include <cstdint>
#include <iostream>
#include <ostream>

#include "util.hpp"
#include "window/window.hpp"

int32_t main() {
    std::ostream& log = std::cerr;

    if (!init_lib(log)) exit(1);

    Window window(log, "Faith: Heaven's Gate", 1000, 800);
    if (!window) exit(1);

    const uint64_t ticks_per_15_fps = (1000 / 15);
    uint64_t       ticks_now, ticks_last_frame = SDL_GetTicks64();

    do {
        window.handle_events();
        ticks_now = SDL_GetTicks64();
        if ((ticks_now - ticks_last_frame) < ticks_per_15_fps)
            SDL_Delay(1);
        else {
            window.clear();
            window.set(200, 200, 0xFFFFFFFF);
            window.set(200, 201, 0xFFFFFFFF);
            window.set(200, 202, 0xFFFFFFFF);
            window.set(200, 203, 0xFFFFFFFF);
            window.set(201, 200, 0xFFFFFFFF);
            window.set(202, 200, 0xFFFFFFFF);
            window.set(203, 200, 0xFFFFFFFF);

            window.set(255, 255, 0x00FFFFFF);
            window.set(0, 0, 0x00FFFFFF);
            window.set(0, 255, 0x00FFFFFF);
            window.set(255, 0, 0x00FFFFFF);
            window.draw();
            ticks_last_frame = ticks_now;
        }
    } while (window);

    SDL_Quit();
    return 0;
}
