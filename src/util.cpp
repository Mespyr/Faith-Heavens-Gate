#include "include/util.h"

void sdl_error(std::string fn) {
	std::cout << "(" << fn << ") Error: " << SDL_GetError() << std::endl;
}
