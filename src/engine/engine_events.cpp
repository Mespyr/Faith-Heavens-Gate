#include "engine.hpp"

bool Engine::running() { return !quit; }

void Engine::handle_events() {
    SDL_Event e;
    while (SDL_PollEvent(&e))
        if (e.type == SDL_QUIT) quit = true;
}
