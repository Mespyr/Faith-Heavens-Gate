#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>

#include <iostream>
#include <ostream>

struct SDL_Deleter {
    void operator()(SDL_Window *p);
    void operator()(SDL_Renderer *p);
    void operator()(SDL_Texture *p);
};

void log_error(std::ostream &log, const std::string &msg);
void log_sdl_error(std::ostream &log, const std::string &sdl_function);
bool init_lib(std::ostream &log);
