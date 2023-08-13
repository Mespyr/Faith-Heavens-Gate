#pragma once

#include "object.h"
#include <cstdint>

class Player {
public:
	Player() {}
	void init_textures(SDL_Texture* player_texture);
	
	Object player_object;
private:
	SDL_Rect left_clips[8];
	SDL_Rect right_clips[8];

	uint32_t animation_frame_index = 0;
};
