#include "../include/engine.h"

bool Engine::running() {
	return !quit;
}

void Engine::handle_events() {
	while (SDL_PollEvent(&e))
		if (e.type == SDL_QUIT)
			quit = true;
}

bool Engine::check_collision(Object* obj1, Object* obj2) {
	// points for object 1's hitbox
	float_t obj1_top_left_x = obj1->position.x,
		obj1_top_left_y = obj1->position.y,
		obj1_bottom_right_x = obj1->position.x + obj1->current_frame.w,
		obj1_bottom_right_y = obj1->position.y + obj1->current_frame.h,
	// points for object 2's hitbox
		obj2_top_left_x = obj2->position.x,
		obj2_top_left_y = obj2->position.y,
		obj2_bottom_right_x = obj2->position.x + obj2->current_frame.w,
		obj2_bottom_right_y = obj2->position.y + obj2->current_frame.h;

	return ((
			 (obj1_top_left_x > obj2_top_left_x && obj1_top_left_x < obj2_bottom_right_x) ||
			 (obj1_bottom_right_x > obj2_top_left_x && obj1_bottom_right_x < obj2_bottom_right_x)
			) && (
			 (obj1_top_left_y > obj2_top_left_y && obj1_top_left_y < obj2_bottom_right_y) ||
			 (obj1_bottom_right_y > obj2_top_left_y && obj1_bottom_right_y < obj2_bottom_right_y)
		   ));
}

void Engine::update(float_t delta_time) {
	kbd_state = SDL_GetKeyboardState(nullptr);
	SDL_GetMouseState(&mouse_position.x, &mouse_position.y);

	// update plater velocity
	if (kbd_state[SDL_SCANCODE_W] || kbd_state[SDL_SCANCODE_A] || kbd_state[SDL_SCANCODE_S] || kbd_state[SDL_SCANCODE_D]) {
		// y movement
		if (kbd_state[SDL_SCANCODE_W])
			player.set_velocity_y(std::max<float>(player.get_velocity_y() - (PLAYER_ACCEL_SPEED * delta_time), -PLAYER_MAX_SPEED));
		else if (kbd_state[SDL_SCANCODE_S])
			player.set_velocity_y(std::min<float>(player.get_velocity_y() + (PLAYER_ACCEL_SPEED * delta_time), PLAYER_MAX_SPEED));
		// if none of y movement keys are being pressed, slow down
		else if (player.get_velocity_y() > 0)
			player.set_velocity_y(std::max<float>(player.get_velocity_y() - (PLAYER_ACCEL_SPEED * delta_time), 0.0f));
		else if (player.get_velocity_y() < 0)
			player.set_velocity_y(std::min<float>(player.get_velocity_y() + (PLAYER_ACCEL_SPEED * delta_time), 0.0f));

		// x movement
		if (kbd_state[SDL_SCANCODE_A])
			player.set_velocity_x(std::max<float>(player.get_velocity_x() - (PLAYER_ACCEL_SPEED * delta_time), -PLAYER_MAX_SPEED));
		else if (kbd_state[SDL_SCANCODE_D])
			player.set_velocity_x(std::min<float>(player.get_velocity_x() + (PLAYER_ACCEL_SPEED * delta_time), PLAYER_MAX_SPEED));
		// if none of x movement keys are being pressed, slow down
		else if (player.get_velocity_x() > 0)
			player.set_velocity_x(std::max<float>(player.get_velocity_x() - (PLAYER_ACCEL_SPEED * delta_time), 0.0f));
		else if (player.get_velocity_x() < 0)
			player.set_velocity_x(std::min<float>(player.get_velocity_x() + (PLAYER_ACCEL_SPEED * delta_time), 0.0f));
	}
	else {
		// decrease x and y velocity since none of the movement keys are being pressed
		if (player.get_velocity_y() > 0)
			player.set_velocity_y(std::max<float>(player.get_velocity_y() - (PLAYER_ACCEL_SPEED * delta_time), 0.0f));
		else if (player.get_velocity_y() < 0)
			player.set_velocity_y(std::min<float>(player.get_velocity_y() + (PLAYER_ACCEL_SPEED * delta_time), 0.0f));
		if (player.get_velocity_x() > 0)
			player.set_velocity_x(std::max<float>(player.get_velocity_x() - (PLAYER_ACCEL_SPEED * delta_time), 0.0f));
		else if (player.get_velocity_x() < 0)
			player.set_velocity_x(std::min<float>(player.get_velocity_x() + (PLAYER_ACCEL_SPEED * delta_time), 0.0f));
	}

	// update player animation
	if (player_animation_timer >= 0.10) {
		player.update_animation_frame(mouse_position, WINDOW_CENTER_X, WINDOW_CENTER_Y);
		player_animation_timer = 0;
	}
	else player_animation_timer += delta_time;

	// update player position and check for collisions
	player.object.update_position(delta_time);

	// check collision with map
	for (Object rect : map_rectangles) {
		if (!rect.collision) continue;
		if (check_collision(&player.object, &rect)) {
			player.object.position -= player.object.velocity * delta_time;
			player.object.velocity.x = 0;
			player.object.velocity.y = 0;
		}
	}
}
