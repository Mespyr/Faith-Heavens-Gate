#pragma once

#include <iostream>
#include <ostream>
#include <SDL2/SDL.h>

void log_error(std::ostream& os, const std::string &msg);
int32_t init_lib();
