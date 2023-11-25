#include "../include/engine.h"

void Engine::render_object(Object* object) {
	if (!is_visible(object)) return;
	SDL_Rect pos;
	float_t transform_x = player.object.position.x - PLAYER_CENTER_X;
	float_t transform_y = player.object.position.y - PLAYER_CENTER_Y;
	pos.x = object->position.x - transform_x;
	pos.y = object->position.y - transform_y;
	pos.w = object->current_frame.w;
	pos.h = object->current_frame.h;
	window.render_texture(object->texture, &object->current_frame, &pos);
}

void Engine::render_scene() {
	window.clear();
	SDL_Rect pos;

	if (background_texture != nullptr) {
		float_t transform_x = player.object.position.x - PLAYER_CENTER_X;
		float_t transform_y = player.object.position.y - PLAYER_CENTER_Y;
		float_t bg_screen_position_x = background_position.x - transform_x;
		float_t bg_screen_position_y = background_position.y - transform_y;

		// background_position represents the position of the top-right
		// texture we are drawing
		if (bg_screen_position_y > 0)
			background_position.y -= window.height();
		else if (-bg_screen_position_y > window.height())
			background_position.y += window.height();

		if (bg_screen_position_x < 0)
			background_position.x += window.width();
		else if (bg_screen_position_x > window.width())
			background_position.x -= window.width();
		
		pos.x = background_position.x - transform_x;
		pos.y = background_position.y - transform_y;
		pos.w = window.width();
		pos.h = window.height();

		window.render_texture(background_texture, nullptr, &pos);
		pos.y += window.height();
		window.render_texture(background_texture, nullptr, &pos);
		pos.x -= window.width();
		window.render_texture(background_texture, nullptr, &pos);
		pos.y -= window.height();
		window.render_texture(background_texture, nullptr, &pos);
	}

	for (Object rect : map_objects)
		render_object(&rect);
	
	pos.x = PLAYER_CENTER_X;
	pos.y = PLAYER_CENTER_Y;
	pos.w = PLAYER_WIDTH;
	pos.h = PLAYER_HEIGHT;
	window.render_texture(player.object.texture, &player.object.current_frame, &pos);
	pos.x = mouse_position.x;
	pos.y = mouse_position.y;
	pos.w = 32;
	pos.h = 32;
	window.render_texture(crosshair_texture, nullptr, &pos);
	window.present();
}
