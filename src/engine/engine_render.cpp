#include "../include/engine.h"

inline void Engine::render_object(Object* object) {
	SDL_Rect pos;
	float_t transform_x = player.object.position.x - PLAYER_CENTER_X;
	float_t transform_y = player.object.position.y - PLAYER_CENTER_Y;
	pos.x = object->position.x - transform_x;
	pos.y = object->position.y - transform_y;
	pos.w = object->current_frame.w;
	pos.h = object->current_frame.h;

	if (!((pos.x + pos.w <= 0) || (pos.x >= (int32_t) WINDOW_WIDTH) ||
		  (pos.y + pos.h <= 0) || (pos.y >= (int32_t) WINDOW_HEIGHT)))
		SDL_RenderCopyEx(renderer, object->texture, &object->current_frame, &pos, object->angle, nullptr, SDL_FLIP_NONE);
}

void Engine::render_scene() {
	SDL_RenderClear(renderer);
	SDL_Rect pos;

	// render the background if set to a texture
	if (background_texture != nullptr) {
		float_t transform_x = player.object.position.x - PLAYER_CENTER_X;
		float_t transform_y = player.object.position.y - PLAYER_CENTER_Y;

		// make sure background_position always has coords for the top-right tile of the background
		// while still being visible on the screen

		if (background_position.y - transform_y > 0)
			background_position.y -= WINDOW_HEIGHT;
		else if (-(background_position.y - transform_y) > WINDOW_HEIGHT)
			background_position.y += WINDOW_HEIGHT;

		if (background_position.x - transform_x < 0)
			background_position.x += WINDOW_WIDTH;
		else if (background_position.x - transform_x > WINDOW_WIDTH)
			background_position.x -= WINDOW_WIDTH;
		
		pos.x = background_position.x - transform_x;
		pos.y = background_position.y - transform_y;
		pos.w = WINDOW_WIDTH;
		pos.h = WINDOW_HEIGHT;

		// draw top right
		SDL_RenderCopy(renderer, background_texture, nullptr, &pos);
		// draw bottom right
		pos.y += WINDOW_HEIGHT;
		SDL_RenderCopy(renderer, background_texture, nullptr, &pos);
		// draw bottom left
		pos.x -= WINDOW_WIDTH;
		SDL_RenderCopy(renderer, background_texture, nullptr, &pos);
		// draw top left
		pos.y -= WINDOW_HEIGHT;
		SDL_RenderCopy(renderer, background_texture, nullptr, &pos);
	}

	// render map
	for (Object rect : map_rectangles)
		render_object(&rect);
	
	// render player at the center of the screen
	pos.x = PLAYER_CENTER_X;
	pos.y = PLAYER_CENTER_Y;
	pos.w = 48;
	pos.h = 48;
	SDL_RenderCopyEx(
	    renderer,
		player.object.texture,
		&player.object.current_frame,
		&pos,
		player.object.angle,
		nullptr,
		SDL_FLIP_NONE
	);

	// render crosshair at mouse position
	pos.x = mouse_position.x;
	pos.y = mouse_position.y;
	pos.w = 32;
	pos.h = 32;
	SDL_RenderCopyEx(
	    renderer,
		crosshair_texture,
		nullptr,
		&pos, 0, nullptr, SDL_FLIP_NONE
	);

	// display everything to screen
	SDL_RenderPresent(renderer);
}
