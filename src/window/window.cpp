#include "window.hpp"

Window::Window(std::ostream& error_log, const std::string& name, uint32_t width,
               uint32_t height)
    : error_log(error_log),
      WIDTH(width),
      HEIGHT(height),
      CENTER_X(width / 2),
      CENTER_Y(height / 2) {
    window = std::unique_ptr<SDL_Window, SDL_Deleter>(
        SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, width, height,
                         SDL_WINDOW_SHOWN),
        SDL_Deleter());

    if (window == nullptr) {
        log_sdl_error(error_log, "SDL_CreateWindow");
        failed = true;
        return;
    }

    renderer = std::unique_ptr<SDL_Renderer, SDL_Deleter>(
        SDL_CreateRenderer(
            window.get(), -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),
        SDL_Deleter());

    if (renderer == nullptr) {
        log_sdl_error(error_log, "SDL_CreateRenderer");
        failed = true;
        return;
    }
}

uint32_t Window::width() { return WIDTH; }
uint32_t Window::height() { return HEIGHT; }
uint32_t Window::center_x() { return CENTER_X; }
uint32_t Window::center_y() { return CENTER_Y; }
