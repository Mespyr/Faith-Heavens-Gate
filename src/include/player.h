#pragma once

#include <cmath>
#include <cstdint>
#include "object.h"
#include "vec2.h"

class Player {
public:
	Player() {}

	Object player_object;
	Object arm_object;

	Vec2<float_t> velocity = {0, 0};

	void init_textures(SDL_Texture* player_texture);
	void update_animation_frame(Vec2<int32_t> mouse_pos, uint32_t window_center_x, uint32_t window_center_y);
	void update_position(float_t delta_time);
private:
	SDL_Rect left_clips[8];
	SDL_Rect right_clips[8];

	uint32_t animation_frame_index = 0;
};
