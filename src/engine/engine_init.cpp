#include "../include/engine.h"

Engine::Engine(std::ostream &error_log_ostream)
	: error_log_ostream(error_log_ostream) {
	SDL_ShowCursor(SDL_FALSE);
}

void Engine::set_window(Window* window_) {
	window = window_;
	PLAYER_CENTER_X = window->center_x() - (PLAYER_WIDTH / 2);
	PLAYER_CENTER_Y = window->center_y() - (PLAYER_HEIGHT / 2);
}

void Engine::init_textures(SDL_Texture* player_texture, SDL_Texture* crosshair_texture_) {
	player.init_textures(player_texture);
	crosshair_texture = crosshair_texture_;
	crosshair_frame.w = 16;
	crosshair_frame.h = 16;
	crosshair_frame.x = 0;
	crosshair_frame.y = 0;
}
