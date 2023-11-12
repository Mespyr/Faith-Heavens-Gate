#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "util.h"
#include "object.h"
#include "vec2.h"
#include "player.h"

enum ObjectCollisionSide {
	NO_COLLISION,
	TOP_COLLISION,
	BOTTOM_COLLISION,
	LEFT_COLLISION,
	RIGHT_COLLISION
};

class Engine {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	static const uint32_t WINDOW_WIDTH = 1920;
	static const uint32_t WINDOW_HEIGHT = 1080;

	static const uint32_t PLAYER_WIDTH = 48;
	static const uint32_t PLAYER_HEIGHT = 48;
	
	static const uint32_t WINDOW_CENTER_X = WINDOW_WIDTH / 2;
	static const uint32_t WINDOW_CENTER_Y = WINDOW_HEIGHT / 2;

	static const uint32_t PLAYER_CENTER_X = WINDOW_CENTER_X - (PLAYER_WIDTH / 2);
	static const uint32_t PLAYER_CENTER_Y = WINDOW_CENTER_Y - (PLAYER_HEIGHT / 2);

	// how many pixels the player can travel in 1 second
	const float_t PLAYER_MAX_SPEED = 400.0f;
	// how much player can accelerate in one second
	// multiply MAX_SPEED by n to get the acceleration needed to go full speed in 1/n of a second
	const float PLAYER_ACCEL_SPEED = PLAYER_MAX_SPEED * 4.0f;

	std::ostream& error_log_ostream = std::cout;

	// background
	SDL_Texture* background_texture = nullptr;
	Vec2<float_t> background_position = {0, 0}; // positon of the top-right copy of the background. the positon of other copies of the background tile will be based off of this

	// crosshair
	SDL_Texture* crosshair_texture;
	SDL_Rect crosshair_frame;
	Vec2<int32_t> mouse_position = {0, 0};

	// checks / states
	const Uint8* kbd_state;
	float_t player_animation_timer = 0;
	bool quit = false;
	SDL_Event e;

	// map loading
	std::vector<Object> map_objects;
public:
	Player player;

	// init
	Engine();
	~Engine();
	int32_t init_window();

	// texture
	SDL_Texture* load_texture(const std::string& file_path);  // load a texture from a file
	void init_textures(
        SDL_Texture* player_texture,
		SDL_Texture* crosshair_texture_
	);  // initialize all textures and objects
	void set_background_texture(SDL_Texture* bg_texture);     // set the background texture

	// util
	bool is_visible(Object* object); // check if object can be visible on the window
	std::pair<ObjectCollisionSide, float_t> check_collision(Object* obj1, Object* obj2);  // check if two objects are intersecting with eachother

	// runtime
	bool running();
	void handle_events();
	void update(float_t delta_time);

	// rendering
	void render_object(Object* object);  // render an object's texture at a location relative to the position of the player
	void render_scene();                 // render all of the objects, the background, and the player

	// map loading
	void map_reset();
	void map_add_rectangle(
		Vec2<float_t> position,
	    uint32_t width,
		uint32_t height,
		uint32_t color,
		bool collision, // if rectangle should collide with player
		uint8_t border_width = 0, // the amount of pixels the border would be
		uint32_t border_color = 0x000000 // color of the border
	);
};
