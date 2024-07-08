#include "../include/engine.h"

bool Engine::is_visible(Object* object) {
    int32_t screen_x =
        object->position.x - (player.object.position.x - PLAYER_CENTER_X);
    int32_t screen_y =
        object->position.y - (player.object.position.y - PLAYER_CENTER_Y);
    return (!((screen_x + object->current_frame.w <= 0) ||
              (screen_x >= (int32_t)window->width()) ||
              (screen_y + object->current_frame.h <= 0) ||
              (screen_y >= (int32_t)window->height())));
}

std::pair<ObjectCollisionSide, float_t> Engine::check_collision(Object* obj1,
                                                                Object* obj2) {
    if (obj1->position.x < obj2->position.x + obj2->current_frame.w &&
        obj1->position.x + obj1->current_frame.w > obj2->position.x &&
        obj1->position.y < obj2->position.y + obj2->current_frame.h &&
        obj1->position.y + obj1->current_frame.h > obj2->position.y) {
        float_t top_collision = abs((obj1->position.y + obj1->current_frame.h) -
                                    obj2->position.y),
                bottom_collision =
                    abs(obj1->position.y -
                        (obj2->position.y + obj2->current_frame.h)),
                left_collision =
                    abs((obj1->position.x + obj1->current_frame.w) -
                        obj2->position.x),
                right_collision =
                    abs(obj1->position.x -
                        (obj2->position.x + obj2->current_frame.w));

        float_t min = top_collision;
        if (bottom_collision < min) min = bottom_collision;
        if (left_collision < min) min = left_collision;
        if (right_collision < min) min = right_collision;

        if (min == top_collision)
            return {ObjectCollisionSide::TOP_COLLISION, min};
        if (min == bottom_collision)
            return {ObjectCollisionSide::BOTTOM_COLLISION, min};
        if (min == left_collision)
            return {ObjectCollisionSide::LEFT_COLLISION, min};
        if (min == right_collision)
            return {ObjectCollisionSide::RIGHT_COLLISION, min};
    }
    return {ObjectCollisionSide::NO_COLLISION, 0};
}
