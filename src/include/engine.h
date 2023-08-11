#pragma once

#include <SDL2/SDL.h>
#include <cstdint>
#include <iostream>

#include "util.h"

class Engine {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	static const uint32_t WINDOW_WIDTH = 900;
	static const uint32_t WINDOW_HEIGHT = 600;
public:
	Engine() {}
	~Engine();

	int32_t init();
};
