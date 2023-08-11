#include "include/engine.h"
#include <SDL2/SDL_rect.h>

Engine::~Engine() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

int32_t Engine::init() {
	window = SDL_CreateWindow(
	    "Pants",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
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

SDL_Texture* Engine::load_texture(const std::string& file_path) {
	SDL_Texture* t = nullptr;
	t = IMG_LoadTexture(renderer, file_path.c_str());
	if (t == nullptr)
		log_error(std::cout, "IMG_LoadTexture");
	return t;
}

void Engine::clear() {
	SDL_RenderClear(renderer);
}

void Engine::render(Object& object, double scale) {
	SDL_Rect pos;
	pos.x = object.position.x - object.current_frame.w;
	pos.y = object.position.y - object.current_frame.h;
	pos.w = object.current_frame.w * scale;
	pos.h = object.current_frame.h * scale;
	SDL_RenderCopyEx(renderer, object.texture, &object.current_frame, &pos, object.angle, nullptr, SDL_FLIP_NONE);
}

void Engine::display() {
	SDL_RenderPresent(renderer);
}
