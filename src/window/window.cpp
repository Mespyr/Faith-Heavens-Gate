#include "window.hpp"

Window::Window(std::ostream& log, const std::string& name, uint32_t width,
               uint32_t height)
    : log(log), WINDOW_WIDTH(width), WINDOW_HEIGHT(height) {
    // create SDL window
    window = std::unique_ptr<SDL_Window, SDL_Deleter>(
        SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, width, height,
                         SDL_WINDOW_SHOWN),
        SDL_Deleter());
    if (window == nullptr) {
        log_sdl_error(log, "SDL_CreateWindow");
        quit = true;
        return;
    }

    // create SDL renderer
    renderer = std::unique_ptr<SDL_Renderer, SDL_Deleter>(
        SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED),
        SDL_Deleter());
    if (renderer == nullptr) {
        log_sdl_error(log, "SDL_CreateRenderer");
        quit = true;
        return;
    }

    // create the screen's texture
    // this is upscaled to cover the screen
    // and is where the entire game is drawn
    SDL_Texture* t =
        SDL_CreateTexture(renderer.get(), SDL_PIXELFORMAT_RGBA8888,
                          SDL_TEXTUREACCESS_STREAMING, GAME_WIDTH, GAME_HEIGHT);
    if (t == nullptr) {
        log_sdl_error(log, "SDL_CreateTexture");
        quit = true;
        return;
    }
    screen_texture =
        std::unique_ptr<SDL_Texture, SDL_Deleter>(t, SDL_Deleter());
}

void Window::draw() {
    SDL_RenderClear(renderer.get());
    SDL_UpdateTexture(screen_texture.get(), nullptr, PIXELS, GAME_WIDTH * 4);
    SDL_RenderCopyEx(renderer.get(), screen_texture.get(), NULL, NULL, 0, NULL,
                     SDL_FLIP_NONE);
    SDL_RenderPresent(renderer.get());
}

void Window::set(uint32_t x, uint32_t y, int32_t color) {
    if (x < GAME_WIDTH && y < GAME_HEIGHT) PIXELS[(y * GAME_WIDTH) + x] = color;
}

void Window::clear() { memset(PIXELS, 0x00000000, sizeof(PIXELS)); }
