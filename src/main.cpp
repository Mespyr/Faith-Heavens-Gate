#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>

#include <cstdint>
#include <iostream>
#include <ostream>

#include "engine/engine.hpp"
#include "util.hpp"
#include "window/window.hpp"

int32_t main() {
    std::ostream& error_log = std::cerr;

    if (!init_lib(error_log)) exit(1);

    Window window(error_log, "Thrifted", 1000, 750);
    if (!window) exit(1);

    Engine engine(error_log, &window);
    if (!engine) exit(1);

    uint64_t ticks_now, ticks_last_frame = SDL_GetTicks64();
    float_t  delta_time;

    do {
        ticks_now = SDL_GetTicks64();
        engine.handle_events();
        if (ticks_last_frame < ticks_now) {
            delta_time = (ticks_now - ticks_last_frame) / 1000.0f;
            engine.render_scene();
        } else
            SDL_Delay(1);
        ticks_last_frame = ticks_now;
    } while (engine.running());

    SDL_Quit();
    return 0;
}
