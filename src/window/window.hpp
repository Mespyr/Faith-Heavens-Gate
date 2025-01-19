#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include <cstdint>
#include <memory>
#include <ostream>
#include <string>

#include "../util.hpp"

class Window {
  public:
    Window(std::ostream& error_log_ostream, const std::string& name,
           uint32_t width, uint32_t height);

    explicit operator bool() const { return !failed; }

    uint32_t width();
    uint32_t height();
    uint32_t center_x();
    uint32_t center_y();

    std::unique_ptr<SDL_Texture, SDL_Deleter> load_texture(
        const std::string& file_path);
    std::unique_ptr<SDL_Texture, SDL_Deleter> create_texture(uint32_t width,
                                                             uint32_t height);

    void render_texture(std::unique_ptr<SDL_Texture, SDL_Deleter> texture,
                        SDL_Rect frame, SDL_Rect position);
    void clear();
    void present();

  private:
    bool          failed = false;
    std::ostream& error_log;

    std::unique_ptr<SDL_Window, SDL_Deleter>   window;
    std::unique_ptr<SDL_Renderer, SDL_Deleter> renderer;

    const uint32_t WIDTH;
    const uint32_t HEIGHT;
    const uint32_t CENTER_X;
    const uint32_t CENTER_Y;
};
