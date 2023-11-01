#include "include/object.h"
#include <iostream>

Object::~Object() {
	SDL_DestroyTexture(texture);
}

void Object::update_position(float_t delta_time) {
	position += velocity * delta_time;
}
