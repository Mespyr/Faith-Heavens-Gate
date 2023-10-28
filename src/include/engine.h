#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <cmath>
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
	static const uint32_t WINDOW_HEIGHT = 720;

	static const uint32_t PLAYER_WIDTH = 48;
	static const uint32_t PLAYER_HEIGHT = 48;
	
	static const uint32_t WINDOW_CENTER_X = WINDOW_WIDTH / 2;
	static const uint32_t WINDOW_CENTER_Y = WINDOW_HEIGHT / 2;

	static const uint32_t PLAYER_CENTER_X = WINDOW_CENTER_X - (PLAYER_WIDTH / 2);
	static const uint32_t PLAYER_CENTER_Y = WINDOW_CENTER_Y - (PLAYER_HEIGHT / 2);

	// how many pixels the player can travel in 1 second
	const float_t PLAYER_MAX_SPEED = 350.0f;
	// how much player can accelerate in one second
	// multiply MAX_SPEED by n to get the acceleration needed to go full speed in 1/n of a second
	const float PLAYER_ACCEL_SPEED = PLAYER_MAX_SPEED * 4.0f;

	// background
	SDL_Texture* background_texture = nullptr;
	Vec2<float_t> background_position = {0, 0}; // positon of the top-right copy of the background. the positon of other copies of the background tile will be based off of this

	// crosshair
	SDL_Texture* crosshair_texture;
	SDL_Rect crosshair_frame;
	Vec2<int32_t> mouse_position = {0, 0};
	
	const Uint8* kbd_state;
	float_t player_animation_timer = 0;
	bool quit = false;
	SDL_Event e;
public:
	Engine();
	~Engine();

	Player player;
	void update_player_animation(Vec2<int32_t> mouse_pos);

	int32_t init_window();
	bool running();
	void handle_events();

	SDL_Texture* load_texture(const std::string& file_path);  // load a texture from a file
	void init_textures(
        SDL_Texture* player_texture,
		SDL_Texture* crosshair_texture_
	);  // initialize all textures and objects
	void set_background_texture(SDL_Texture* bg_texture);     // set the background texture

	bool check_collision(Object obj1, Object obj2);  // check if two objects' hitboxes are intersecting with eachother

	void render_object(Object& object);  // render an object's texture at a location relative to the position of the player
	void update(float_t delta_time);     // handle game updates
	void render_scene();                 // render all of the objects, the background, and the player

	// TEST
	Object test_obj;
};
