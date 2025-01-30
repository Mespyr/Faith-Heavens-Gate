#include "util.hpp"

void SDL_Deleter::operator()(SDL_Window *p) { SDL_DestroyWindow(p); }
void SDL_Deleter::operator()(SDL_Renderer *p) { SDL_DestroyRenderer(p); }
void SDL_Deleter::operator()(SDL_Texture *p) { SDL_DestroyTexture(p); }

void log_error(std::ostream &log, const std::string &msg) {
    log << "error: " << msg << std::endl;
}

void log_sdl_error(std::ostream &log, const std::string &sdl_function) {
    log << sdl_function << " error: " << SDL_GetError() << std::endl;
}

bool init_lib(std::ostream &log) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        log_sdl_error(log, "SDL_Init");
        return false;
    }
    log << "SDL successfully initialized." << std::endl;
    return true;
}
