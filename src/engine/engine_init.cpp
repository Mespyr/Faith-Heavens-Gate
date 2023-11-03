#include "../include/engine.h"

Engine::Engine() {
	SDL_ShowCursor(SDL_FALSE);
}

Engine::~Engine() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

int32_t Engine::init_window() {
	window = SDL_CreateWindow(
	    "Pants",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		//SDL_WINDOW_FULLSCREEN_DESKTOP
		SDL_WINDOW_SHOWN
	);

	if (window == nullptr) {
		log_error(std::cout, "SDL_CreateWindow");
		return 1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		log_error(std::cout, "SDL_CreateRenderer");
		return 1;
	}

	return 0;
}
