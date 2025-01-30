#include "window.hpp"

Window::Window(std::ostream& log, const std::string& name, uint32_t width,
               uint32_t height, Palette palette)
    : name(name),
      WINDOW_WIDTH(width),
      WINDOW_HEIGHT(height),
      log(log),
      palette(palette) {
    // dont blur the window texture
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);
    if (!create_window() || !create_renderer() || !create_game_texture() ||
        !create_scanline_texture()) {
        quit = true;
        return;
    }
    // reset renderer target, now ready to draw frames
    SDL_SetRenderTarget(renderer.get(), NULL);
}

void Window::handle_events() {
    SDL_Event e;
    while (SDL_PollEvent(&e))
        if (e.type == SDL_QUIT) quit = true;
}
