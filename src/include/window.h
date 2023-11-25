#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>
#include <cstdint>
#include <ostream>
#include <string>

#include "util.h"

class Window {
public:
	bool fail_init = false;

	Window(std::ostream &error_log_ostream, const char* name, uint32_t width, uint32_t height);
	~Window();

	uint32_t width();
	uint32_t height();
	uint32_t center_x();
	uint32_t center_y();

	SDL_Texture* load_texture(const char* file_path);
	SDL_Texture* create_texture(uint32_t width, uint32_t height);
	void render_texture(SDL_Texture* texture, SDL_Rect* frame, SDL_Rect* position);

	void clear();
	void present();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::ostream& error_log_ostream;

	const uint32_t WINDOW_WIDTH;
	const uint32_t WINDOW_HEIGHT;
	const uint32_t WINDOW_CENTER_X;
	const uint32_t WINDOW_CENTER_Y;
};
