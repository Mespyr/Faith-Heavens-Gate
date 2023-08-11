#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdint>
#include <iostream>
#include <string>

#include "util.h"
#include "object.h"

class Engine {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	static const uint32_t WINDOW_WIDTH = 1280;
	static const uint32_t WINDOW_HEIGHT = 720;
public:
	Engine() {}
	~Engine();

	int32_t init();
	SDL_Texture* load_texture(const std::string& file_path);
	void clear();
	void render(Object& object, double scale);
	void display();
};
