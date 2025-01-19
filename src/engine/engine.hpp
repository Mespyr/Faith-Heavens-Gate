#pragma once

#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_stdinc.h>

#include <cstdint>
#include <ostream>

#include "../window/window.hpp"

class Engine {
  public:
    Engine(std::ostream& error_log, Window* window);

    explicit operator bool() const { return !failed; }

    // events
    bool running();
    void handle_events();

    // render pipeline
    void render_scene();

  private:
    bool          failed = false;
    std::ostream& error_log;

    Window* window;

    const Uint8* kbd_state;
    float_t      player_animation_timer = 0;
    bool         quit = false;

    const uint32_t WIDTH = 400;
    const uint32_t HEIGHT = 300;
};
