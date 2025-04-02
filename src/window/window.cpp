#include "window.hpp"

Window::Window(std::ostream& log, const std::string& name, uint32_t width,
               uint32_t height, Palette palette)
    : name(name),
      WINDOW_WIDTH(width),
      WINDOW_HEIGHT(height),
      log(log),
      palette(palette) {
    if (!create_window() || !create_renderer() || !create_game_texture() ||
        !create_scanline_texture()) {
        quit = true;
        return;
    }
}

void Window::handle_events() {
    SDL_Event e;
    while (SDL_PollEvent(&e))
        if (e.type == SDL_EVENT_QUIT) quit = true;
}
