#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "vec2.h"

class Object {
public:
	Object() {}
	Object(float_t x, float_t y, SDL_Texture* texture) 
		: position(x, y), texture(texture)
	{}

	Object(Vec2<float_t> position, SDL_Texture* texture)
		: position(position), texture(texture)
	{}

	bool collision = false;
	Vec2<float_t> position;
	Vec2<float_t> velocity = {0, 0};
	SDL_Texture* texture;
	SDL_Rect current_frame;
	float_t angle = 0;

	void update_position(float_t delta_time);
};
