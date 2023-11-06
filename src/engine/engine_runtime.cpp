#include "../include/engine.h"

bool Engine::running() {
	return !quit;
}

void Engine::handle_events() {
	while (SDL_PollEvent(&e))
		if (e.type == SDL_QUIT)
			quit = true;
}

std::pair<ObjectCollisionSide, float_t> Engine::check_collision(Object* obj1, Object* obj2) {
	// returns what side OBJ1 is colliding with OBJ2
	if (obj1->position.x < obj2->position.x + obj2->current_frame.w && obj1->position.x + obj1->current_frame.w > obj2->position.x &&
		obj1->position.y < obj2->position.y + obj2->current_frame.h && obj1->position.y + obj1->current_frame.h > obj2->position.y) {

		// check which side is most intersecting
		float_t top_collision = abs((obj1->position.y + obj1->current_frame.h) - obj2->position.y),
			bottom_collision = abs(obj1->position.y - (obj2->position.y + obj2->current_frame.h)),
			left_collision = abs((obj1->position.x + obj1->current_frame.w) - obj2->position.x),
			right_collision = abs(obj1->position.x - (obj2->position.x + obj2->current_frame.w));
		
		float_t min = top_collision;
		if (bottom_collision < min) min = bottom_collision;
		if (left_collision < min) min = left_collision;
		if (right_collision < min) min = right_collision;

		if (min == top_collision) return {ObjectCollisionSide::TOP_COLLISION, min};
		if (min == bottom_collision) return {ObjectCollisionSide::BOTTOM_COLLISION, min};
		if (min == left_collision) return {ObjectCollisionSide::LEFT_COLLISION, min};
		if (min == right_collision) return {ObjectCollisionSide::RIGHT_COLLISION, min};
	}
	return {ObjectCollisionSide::NO_COLLISION, 0};
}

void Engine::update(float_t delta_time) {
	kbd_state = SDL_GetKeyboardState(nullptr);
	SDL_GetMouseState(&mouse_position.x, &mouse_position.y);

	if (kbd_state[SDL_SCANCODE_C])
		map_reset();
	
	// y velocity
	if (kbd_state[SDL_SCANCODE_W] || kbd_state[SDL_SCANCODE_S]) {
		if (kbd_state[SDL_SCANCODE_W])
			player.set_velocity_y(std::max<float>(player.get_velocity_y() - (PLAYER_ACCEL_SPEED * delta_time), -PLAYER_MAX_SPEED));
		if (kbd_state[SDL_SCANCODE_S])
			player.set_velocity_y(std::min<float>(player.get_velocity_y() + (PLAYER_ACCEL_SPEED * delta_time), PLAYER_MAX_SPEED));
	}
	else if (player.get_velocity_y() > 0)
		player.set_velocity_y(std::max<float>(player.get_velocity_y() - (PLAYER_ACCEL_SPEED * delta_time), 0.0f));
	else if (player.get_velocity_y() < 0)
		player.set_velocity_y(std::min<float>(player.get_velocity_y() + (PLAYER_ACCEL_SPEED * delta_time), 0.0f));

	// x velocity
	if (kbd_state[SDL_SCANCODE_A] || kbd_state[SDL_SCANCODE_D]) {
		if (kbd_state[SDL_SCANCODE_A])
			player.set_velocity_x(std::max<float>(player.get_velocity_x() - (PLAYER_ACCEL_SPEED * delta_time), -PLAYER_MAX_SPEED));
		if (kbd_state[SDL_SCANCODE_D])
			player.set_velocity_x(std::min<float>(player.get_velocity_x() + (PLAYER_ACCEL_SPEED * delta_time), PLAYER_MAX_SPEED));
	}
	else if (player.get_velocity_x() > 0)
		player.set_velocity_x(std::max<float>(player.get_velocity_x() - (PLAYER_ACCEL_SPEED * delta_time), 0.0f));
	else if (player.get_velocity_x() < 0)
		player.set_velocity_x(std::min<float>(player.get_velocity_x() + (PLAYER_ACCEL_SPEED * delta_time), 0.0f));

	// update player animation
	if (player_animation_timer >= 0.10) {
		player.update_animation_frame(mouse_position, WINDOW_CENTER_X, WINDOW_CENTER_Y);
		player_animation_timer = 0;
	}
	else player_animation_timer += delta_time;

	// check collision with map
	for (Object rect : map_objects) {
		if (!rect.collision) continue;
		std::pair<ObjectCollisionSide, float_t> collision = check_collision(&player.object, &rect);
		switch (collision.first) {
		case ObjectCollisionSide::TOP_COLLISION:
			player.object.position.y -= collision.second;
			player.object.velocity.y = 0;
			break;
		case ObjectCollisionSide::BOTTOM_COLLISION:
			player.object.position.y += collision.second;
			player.object.velocity.y = 0;
			break;
		case ObjectCollisionSide::LEFT_COLLISION:
			player.object.position.x -= collision.second;
			player.object.velocity.x = 0;
			break;
		case ObjectCollisionSide::RIGHT_COLLISION:
			player.object.position.x += collision.second;
			player.object.velocity.x = 0;
			break;
		case ObjectCollisionSide::NO_COLLISION:
			break;
		}
	}

	// update player position and check for collisions
	player.object.update_position(delta_time);
}
