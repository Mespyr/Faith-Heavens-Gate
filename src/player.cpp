#include "include/player.h"

void Player::init_textures(SDL_Texture* player_texture) {
	object.texture = player_texture;

	// left
	for (int i = 0; i < 8; i++) {
		left_clips[i].x = i * 48;
		left_clips[i].y = 0; // 48 * 0
		left_clips[i].w = 48;
		left_clips[i].h = 48;
	}
	// right
	for (int i = 0; i < 8; i++) {
		right_clips[i].x = i * 48;
		right_clips[i].y = 48; // 48 * 1
		right_clips[i].w = 48;
		right_clips[i].h = 48;
	}
	// down
	for (int i = 0; i < 8; i++) {
		down_clips[i].x = i * 48;
		down_clips[i].y = 96; // 48 * 2
		down_clips[i].w = 48;
		down_clips[i].h = 48;
	}
	// up
	for (int i = 0; i < 8; i++) {
		up_clips[i].x = i * 48;
		up_clips[i].y = 144; // 48 * 3
		up_clips[i].w = 48;
		up_clips[i].h = 48;
	}

	// set player default clip
	object.current_frame = right_clips[0];
}

void Player::update_animation_frame(Vec2<int32_t> mouse_pos, uint32_t window_center_x, uint32_t window_center_y) {
	// change animation frame
	if (object.velocity.x != 0 || object.velocity.y != 0) {
		animation_frame_index += 1;
		if (animation_frame_index == 8) animation_frame_index = 0;
	}
	else animation_frame_index = 0;
	float_t player_mouse_angle = atan2((int32_t) window_center_y - mouse_pos.y, (int32_t) window_center_x - mouse_pos.x) * 180 / 3.1415;

	// left
	if ((player_mouse_angle >= 0 && player_mouse_angle <= 45) || (player_mouse_angle <= 0 && player_mouse_angle >= -45))
		object.current_frame = left_clips[animation_frame_index];
	// right
	else if ((player_mouse_angle >= 135 && player_mouse_angle <= 180) || (player_mouse_angle <= -135 && player_mouse_angle >= -180))
		object.current_frame = right_clips[animation_frame_index];
	// up
	else if (player_mouse_angle >= 45 && player_mouse_angle <= 135)
		object.current_frame = up_clips[animation_frame_index];
	// down
	else if (player_mouse_angle <= -45 && player_mouse_angle >= -135)
		object.current_frame = down_clips[animation_frame_index];
}

void Player::set_velocity_y(float_t y) {
	object.velocity.y = y;
}

void Player::set_velocity_x(float_t x) {
	object.velocity.x = x;
}

float_t Player::get_velocity_y() {
	return object.velocity.y;
}

float_t Player::get_velocity_x() {
	return object.velocity.x;
}
