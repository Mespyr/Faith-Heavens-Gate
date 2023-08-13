#include "include/engine.h"

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

void Engine::init_textures(SDL_Texture* player_texture) {
	player.init_textures(player_texture);
}

void Engine::clear() {
	SDL_RenderClear(renderer);
}

void Engine::display() {
	SDL_RenderPresent(renderer);
}

SDL_Texture* Engine::load_texture(const std::string& file_path) {
	SDL_Texture* t = nullptr;
	t = IMG_LoadTexture(renderer, file_path.c_str());
	if (t == nullptr)
		log_error(std::cout, "IMG_LoadTexture");
	return t;
}

void Engine::render_object(Object& object) {
	SDL_Rect pos;

	int32_t transform_x = player.player_object.position.x - PLAYER_CENTER_X;
	int32_t transform_y = player.player_object.position.y - PLAYER_CENTER_Y;
	
	pos.x = object.position.x - transform_x;
	pos.y = object.position.y - transform_y;
	pos.w = object.current_frame.w * WINDOW_SCALE;
	pos.h = object.current_frame.h * WINDOW_SCALE;
	SDL_RenderCopyEx(
        renderer,
		object.texture,
		&object.current_frame,
		&pos,
		object.angle,
		nullptr,
		SDL_FLIP_NONE
	);
}

void Engine::render_player() {
	SDL_Rect pos;
	pos.x = PLAYER_CENTER_X;
	pos.y = PLAYER_CENTER_Y;
	pos.w = 16 * WINDOW_SCALE;
	pos.h = 16 * WINDOW_SCALE;
	SDL_RenderCopyEx(
	    renderer,
		player.player_object.texture,
		&player.player_object.current_frame,
		&pos,
		player.player_object.angle,
		nullptr,
		SDL_FLIP_NONE
	);
}
