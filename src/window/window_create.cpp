#include "window.hpp"

std::unique_ptr<SDL_Texture, SDL_Deleter> Window::load_texture(
    const std::string& file_path) {
    SDL_Texture* t = IMG_LoadTexture(renderer.get(), file_path.c_str());
    if (t == nullptr) log_sdl_error(error_log, "IMG_LoadTexture");
    return std::unique_ptr<SDL_Texture, SDL_Deleter>(t, SDL_Deleter());
}

std::unique_ptr<SDL_Texture, SDL_Deleter> Window::create_texture(
    uint32_t width, uint32_t height) {
    SDL_Texture* t =
        SDL_CreateTexture(renderer.get(), SDL_PIXELFORMAT_RGB888,
                          SDL_TEXTUREACCESS_STREAMING, width, height);
    if (t == nullptr) log_sdl_error(error_log, "SDL_CreateTexture");
    return std::unique_ptr<SDL_Texture, SDL_Deleter>(t, SDL_Deleter());
}
