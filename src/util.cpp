#include "include/util.h"

void log_error(std::ostream& os, const std::string& msg) {
    os << msg << " error: " << SDL_GetError() << std::endl;
}

int32_t init_lib() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        log_error(std::cout, "SDL_Init");
        return 1;
    }
    return 0;
}
