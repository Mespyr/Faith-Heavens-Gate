#include "include/player.h"

void Player::init_textures(SDL_Texture* player_texture) {
	player_object.texture = player_texture;

	// save clips for walking left
	for (int i = 0; i < 8; i++) {
		left_clips[i].x = i * 16;
		left_clips[i].y = 0;
		left_clips[i].w = 16;
		left_clips[i].h = 16;
	}

	// save clips for walking right
	for (int i = 0; i < 8; i++) {
		right_clips[i].x = i * 16;
		right_clips[i].y = 16;
		right_clips[i].w = 16;
		right_clips[i].h = 16;
	}

	// set player default clip
	player_object.current_frame = left_clips[6];
}
