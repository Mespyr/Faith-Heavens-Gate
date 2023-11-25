#pragma once

#include <cmath>
#include <cstdint>
#include "object.h"
#include "vec2.h"

class Player {
public:
	Player() {}

	Object object;

	void init_textures(SDL_Texture* player_texture);
	void update_animation_frame(Vec2<int32_t> mouse_pos, uint32_t window_center_x, uint32_t window_center_y);

	void set_velocity_y(float_t y);
	void set_velocity_x(float_t x);
	float_t get_velocity_y();
	float_t get_velocity_x();
private:
	SDL_Rect left_clips[8];
	SDL_Rect right_clips[8];
	SDL_Rect up_clips[8];
	SDL_Rect down_clips[8];
	uint32_t animation_frame_index = 0;
	static const uint32_t PLAYER_ANIMATION_FRAME_COUNT = 8;
};
