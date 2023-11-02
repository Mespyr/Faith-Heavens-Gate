#include "include/object.h"
#include <iostream>

void Object::update_position(float_t delta_time) {
	position += velocity * delta_time;
}
