#include "window.hpp"

void Window::draw() {
    SDL_RenderClear(renderer.get());
    SDL_UpdateTexture(game_texture.get(), nullptr, PIXELS,
                      GAME_WIDTH * sizeof(uint32_t));
    SDL_RenderCopy(renderer.get(), game_texture.get(), NULL, NULL);
    SDL_RenderCopy(renderer.get(), scanline_texture.get(), NULL, NULL);
    SDL_RenderPresent(renderer.get());
}

void Window::set(uint32_t x, uint32_t y, Palette::Color color) {
    if (x < GAME_WIDTH && y < GAME_HEIGHT)
        PIXELS[(y * GAME_WIDTH) + x] = palette.get(color);
}

void Window::clear() {
    memset(PIXELS, palette.get(Palette::BLACK), sizeof(PIXELS));
}
