#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdint>
#include <iostream>
#include <string>

#include "util.h"
#include "object.h"
#include "vec2.h"
#include "player.h"

class Engine {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	static const uint32_t WINDOW_WIDTH = 1280;
	static const uint32_t WINDOW_HEIGHT = 1000;
	static const uint32_t WINDOW_SCALE = 4;

	static const uint32_t WINDOW_CENTER_X = WINDOW_WIDTH / 2;
	static const uint32_t WINDOW_CENTER_Y = WINDOW_HEIGHT / 2;

	static const uint32_t PLAYER_CENTER_X = WINDOW_CENTER_X - (8 * WINDOW_SCALE);
	static const uint32_t PLAYER_CENTER_Y = WINDOW_CENTER_Y - (8 * WINDOW_SCALE);
public:
	Engine() {}
	~Engine();

	Player player;
	
	int32_t init_window();                                   // initialize the window and the renderer
	void init_textures(SDL_Texture* player_texture);         // initialize all textures and objects

	void clear();
	void display();
	
	SDL_Texture* load_texture(const std::string& file_path); // load a texture from a file
	void render_object(Object& object);                      // render an object's texture at a location relative to the position of the player
	void render_player();                                    // render the player at the center of the screen
};
