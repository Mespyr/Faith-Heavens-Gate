#include "window.hpp"

void Window::render_texture(std::unique_ptr<SDL_Texture, SDL_Deleter> texture,
                            SDL_Rect frame, SDL_Rect position) {
    SDL_RenderCopyEx(renderer.get(), texture.get(), &frame, &position, 0,
                     nullptr, SDL_FLIP_NONE);
}

void Window::clear() { SDL_RenderClear(renderer.get()); }

void Window::present() { SDL_RenderPresent(renderer.get()); }
