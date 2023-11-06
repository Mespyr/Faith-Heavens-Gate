#include "../include/engine.h"
#include <cstdint>

void Engine::map_reset() {
	for (Object rect : map_objects)
		SDL_DestroyTexture(rect.texture);
	map_objects.clear();
}

void Engine::map_add_rectangle(Vec2<float_t> position, uint32_t width, uint32_t height, uint32_t color, bool collision, uint8_t border_width, uint32_t border_color) {
	Object rect;
	rect.texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, width, height);
	rect.current_frame.x = 0;
	rect.current_frame.y = 0;
	rect.current_frame.w = width;
	rect.current_frame.h = height;
	rect.position = position;
	rect.collision = collision;

	uint32_t* pixels = (uint32_t*) malloc(width * height * sizeof(uint32_t));

	// since there is no border, we can just fill the whole rectangle with one color
	if (border_width == 0)
		for (uint32_t p = 0; p < (width * height); p++)
			pixels[p] = color;
	else {
		// set border
		for (uint32_t p = 0; p < (width * height); p++)
			pixels[p] = border_color;

		// color non border parts
		for (uint32_t h = border_width; h < height - border_width; h++)
			for (uint32_t w = border_width; w < width - border_width; w++)
				pixels[width * h + w] = color;
	}

	SDL_UpdateTexture(rect.texture, nullptr, pixels, width * sizeof(uint32_t));
	free(pixels);
	map_objects.push_back(rect);
}
