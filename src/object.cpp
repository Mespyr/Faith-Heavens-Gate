#include "include/object.h"

void Object::update_position(float_t delta_time) {
    position += velocity * delta_time;
}
