#include "engine.hpp"

Engine::Engine(std::ostream& error_log, Window* window)
    : error_log(error_log), window(window) {
    SDL_ShowCursor(SDL_FALSE);
    const float_t aspect_ratio_width = window->width() / WIDTH;
    const float_t aspect_ratio_height = window->height() / HEIGHT;
    if (aspect_ratio_width != aspect_ratio_height) {
        log_error(
            error_log,
            "size of window doesn't match the set aspect ratio of the engine.");
        failed = true;
    }
}
