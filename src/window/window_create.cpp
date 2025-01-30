#include "window.hpp"

bool Window::create_window() {
    window = std::unique_ptr<SDL_Window, SDL_Deleter>(
        SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT,
                         SDL_WINDOW_SHOWN),
        SDL_Deleter());
    if (window == nullptr) {
        log_sdl_error(log, "SDL_CreateWindow");
        return false;
    }
    return true;
}

bool Window::create_renderer() {
    renderer = std::unique_ptr<SDL_Renderer, SDL_Deleter>(
        SDL_CreateRenderer(
            window.get(), -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE),
        SDL_Deleter());
    if (renderer == nullptr) {
        log_sdl_error(log, "SDL_CreateRenderer");
        return false;
    }
    SDL_SetRenderDrawBlendMode(renderer.get(), SDL_BLENDMODE_BLEND);
    return true;
}

bool Window::create_game_texture() {
    // create the games's texture at native resolution
    // using TEXTUREACCESS_STREAMING to edit individual pixels
    SDL_Texture* game_texture_ptr =
        SDL_CreateTexture(renderer.get(), SDL_PIXELFORMAT_RGB888,
                          SDL_TEXTUREACCESS_STREAMING, GAME_WIDTH, GAME_HEIGHT);
    if (game_texture_ptr == nullptr) {
        log_sdl_error(log, "SDL_CreateTexture");
        return false;
    }
    game_texture = std::unique_ptr<SDL_Texture, SDL_Deleter>(game_texture_ptr,
                                                             SDL_Deleter());
    SDL_SetTextureBlendMode(game_texture.get(), SDL_BLENDMODE_BLEND);
    return true;
}

bool Window::create_scanline_texture() {
    // create the scanline effect in a texture
    // using TEXTUREACCESS_TARGET to draw using the renderer
    SDL_Texture* scanline_texture_ptr = SDL_CreateTexture(
        renderer.get(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
        GAME_WIDTH * 2, GAME_HEIGHT * 2);
    if (scanline_texture_ptr == nullptr) {
        log_sdl_error(log, "SDL_CreateTexture");
        return false;
    }
    scanline_texture = std::unique_ptr<SDL_Texture, SDL_Deleter>(
        scanline_texture_ptr, SDL_Deleter());
    SDL_SetTextureBlendMode(scanline_texture.get(), SDL_BLENDMODE_BLEND);

    // draw scanlines onto the texture using the renderer
    SDL_SetRenderTarget(renderer.get(), scanline_texture.get());
    SDL_SetRenderDrawColor(renderer.get(), 0xFF, 0xFF, 0xFF, 0x00);
    SDL_RenderFillRect(renderer.get(), NULL);
    SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 0x40);
    for (uint32_t i = 0; i < GAME_HEIGHT * 2; i += 2)
        SDL_RenderDrawLine(renderer.get(), 0, i, GAME_WIDTH * 2, i);
    return true;
}
