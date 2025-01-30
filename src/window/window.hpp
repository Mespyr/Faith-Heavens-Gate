#pragma once

#include <SDL3/SDL.h>

#include <cstdint>
#include <cstring>
#include <memory>
#include <ostream>
#include <string>

#include "../palette.hpp"
#include "../util.hpp"

class Window {
  public:
    Window(std::ostream& log, const std::string& name, uint32_t width,
           uint32_t height, Palette palette);

    explicit operator bool() const { return !quit; }

    std::unique_ptr<SDL_Texture, SDL_Deleter> load_texture(
        const std::string& file_path);

    void clear();
    void draw();
    void handle_events();
    void set(uint32_t x, uint32_t y, Palette::Color color);

  private:
    const std::string& name;
    const uint32_t     WINDOW_WIDTH, WINDOW_HEIGHT;
    bool               quit = false;
    std::ostream&      log;

    // native game resolution
    static const uint32_t GAME_WIDTH = 240, GAME_HEIGHT = 135;
    int32_t               PIXELS[GAME_WIDTH * GAME_HEIGHT];
    static const uint32_t SCANLINE_WIDTH = GAME_WIDTH * 2,
                          SCANLINE_HEIGHT = GAME_HEIGHT * 2;

    std::unique_ptr<SDL_Window, SDL_Deleter>   window;
    std::unique_ptr<SDL_Renderer, SDL_Deleter> renderer;
    std::unique_ptr<SDL_Texture, SDL_Deleter>  game_texture;
    std::unique_ptr<SDL_Texture, SDL_Deleter>  scanline_texture;
    Palette                                    palette;

    bool create_window();
    bool create_renderer();
    bool create_game_texture();
    bool create_scanline_texture();
};
