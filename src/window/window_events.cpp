#include "window.hpp"

void Window::handle_events() {
    SDL_Event e;
    while (SDL_PollEvent(&e))
        if (e.type == SDL_QUIT) quit = true;
}
