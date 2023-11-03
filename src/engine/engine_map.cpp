#include "../include/engine.h"

void Engine::map_reset() {
	for (Object rect : map_rectangles)
		SDL_DestroyTexture(rect.texture);
	map_rectangles.clear();
}

void Engine::map_add_rectangle(Vec2<float_t> position, uint32_t width, uint32_t height, uint32_t color, bool filled, uint32_t border_width, bool collision) {
	Object rect;
	rect.texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
	rect.current_frame.x = 0;
	rect.current_frame.y = 0;
	rect.current_frame.w = width;
	rect.current_frame.h = height;
	rect.position = position;
	rect.collision = collision;

	uint32_t* pixels = (uint32_t*) malloc(width * height * sizeof(uint32_t));

	// TODO: 'filled' and 'border_width'
	for (uint32_t p = 0; p < (width * height); p++)
		pixels[p] = color;

	SDL_UpdateTexture(rect.texture, nullptr, pixels, width * sizeof(uint32_t));
	map_rectangles.push_back(rect);
}
