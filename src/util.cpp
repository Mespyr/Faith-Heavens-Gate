#include "util.hpp"

void SDL_Deleter::operator()(SDL_Window *p) { SDL_DestroyWindow(p); }
void SDL_Deleter::operator()(SDL_Renderer *p) { SDL_DestroyRenderer(p); }
void SDL_Deleter::operator()(SDL_Texture *p) { SDL_DestroyTexture(p); }

void log_error(std::ostream &error_log, const std::string &msg) {
    error_log << "error: " << msg << std::endl;
}

void log_sdl_error(std::ostream &error_log, const std::string &sdl_function) {
    error_log << sdl_function << " error: " << SDL_GetError() << std::endl;
}

bool init_lib(std::ostream &error_log) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        log_error(error_log, "SDL_Init");
        return false;
    }
    error_log << "SDL2 successfully initialized." << std::endl;
    return true;
}
