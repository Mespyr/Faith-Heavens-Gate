#include <cstdint>
#include <iostream>
#include <SDL2/SDL.h>

#include "include/util.h"

int32_t main() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		sdl_error("SDL_Init");
		return 1;
	}
	std::cout << "Hello World!" << std::endl;
	SDL_Quit();
	return 0;
}
