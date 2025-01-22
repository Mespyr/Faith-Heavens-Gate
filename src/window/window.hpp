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
    Window(std::ostream& log, const std::string& name, uint32_t width,
           uint32_t height);

    explicit operator bool() const { return !quit; }

    std::unique_ptr<SDL_Texture, SDL_Deleter> load_texture(
        const std::string& file_path);

    void clear();
    void draw();
    void handle_events();
    void set(uint32_t x, uint32_t y, int32_t color);

  private:
    bool          quit = false;
    std::ostream& log;

    std::unique_ptr<SDL_Window, SDL_Deleter>   window;
    std::unique_ptr<SDL_Renderer, SDL_Deleter> renderer;
    std::unique_ptr<SDL_Texture, SDL_Deleter>  screen_texture;

    const uint32_t        WINDOW_WIDTH, WINDOW_HEIGHT;
    static const uint32_t GAME_WIDTH = 256, GAME_HEIGHT = 256;
    int32_t               PIXELS[GAME_WIDTH * GAME_HEIGHT];
};
