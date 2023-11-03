#include "../include/engine.h"

SDL_Texture* Engine::load_texture(const std::string& file_path) {
	SDL_Texture* t = nullptr;
	t = IMG_LoadTexture(renderer, file_path.c_str());
	if (t == nullptr)
		log_error(std::cout, "IMG_LoadTexture");
	return t;
}

void Engine::init_textures(SDL_Texture* player_texture, SDL_Texture* crosshair_texture_) {
	player.init_textures(player_texture);
	crosshair_texture = crosshair_texture_;
	crosshair_frame.w = 16;
	crosshair_frame.h = 16;
	crosshair_frame.x = 0;
	crosshair_frame.y = 0;
}

void Engine::set_background_texture(SDL_Texture* bg_texture) {
	background_texture = bg_texture;
	background_position = {0, 0};
}
