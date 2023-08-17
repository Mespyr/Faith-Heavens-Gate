#include "include/engine.h"

Engine::~Engine() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

int32_t Engine::init_window() {
	window = SDL_CreateWindow(
	    "Pants",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN
	);

	if (window == nullptr) {
		log_error(std::cout, "SDL_CreateWindow");
		return 1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		log_error(std::cout, "SDL_CreateRenderer");
		return 1;
	}

	return 0;
}

SDL_Texture* Engine::load_texture(const std::string& file_path) {
	SDL_Texture* t = nullptr;
	t = IMG_LoadTexture(renderer, file_path.c_str());
	if (t == nullptr)
		log_error(std::cout, "IMG_LoadTexture");
	return t;
}

void Engine::init_textures(SDL_Texture* player_texture, SDL_Texture* arm_texture) {
	player.init_textures(player_texture, arm_texture);
}

void Engine::set_background_texture(SDL_Texture* bg_texture) {
	background_texture = bg_texture;
	background_position = {0, 0};
}

void Engine::clear() {
	SDL_RenderClear(renderer);
}

void Engine::render_object(Object& object) {
	SDL_Rect pos;
	int32_t transform_x = player.player_object.position.x - PLAYER_CENTER_X;
	int32_t transform_y = player.player_object.position.y - PLAYER_CENTER_Y;
	pos.x = object.position.x - transform_x;
	pos.y = object.position.y - transform_y;
	pos.w = object.current_frame.w * WINDOW_SCALE;
	pos.h = object.current_frame.h * WINDOW_SCALE;
	SDL_RenderCopyEx(
        renderer,
		object.texture,
		&object.current_frame,
		&pos,
		object.angle,
		nullptr,
		SDL_FLIP_NONE
	);
}

void Engine::update(float_t delta_time) {
	kbd_state = SDL_GetKeyboardState(nullptr);
	SDL_GetMouseState(&mouse_position.x, &mouse_position.y);

	// update plater velocity
	if (kbd_state[SDL_SCANCODE_W] || kbd_state[SDL_SCANCODE_A] || kbd_state[SDL_SCANCODE_S] || kbd_state[SDL_SCANCODE_D]) {
		// y movement
		if (kbd_state[SDL_SCANCODE_W])
			player.velocity.y = std::max<float>(player.velocity.y - (PLAYER_ACCEL_SPEED * delta_time), -PLAYER_MAX_SPEED);
		else if (kbd_state[SDL_SCANCODE_S])
			player.velocity.y = std::min<float>(player.velocity.y + (PLAYER_ACCEL_SPEED * delta_time), PLAYER_MAX_SPEED);
		// if none of y movement keys are being pressed, slow down
		else if (player.velocity.y > 0)
			player.velocity.y = std::max<float>(player.velocity.y - (PLAYER_ACCEL_SPEED * delta_time), 0.0f);
		else if (player.velocity.y < 0)
			player.velocity.y = std::min<float>(player.velocity.y + (PLAYER_ACCEL_SPEED * delta_time), 0.0f);

		// x movement
		if (kbd_state[SDL_SCANCODE_A])
			player.velocity.x = std::max<float>(player.velocity.x - (PLAYER_ACCEL_SPEED * delta_time), -PLAYER_MAX_SPEED);
		else if (kbd_state[SDL_SCANCODE_D])
			player.velocity.x = std::min<float>(player.velocity.x + (PLAYER_ACCEL_SPEED * delta_time), PLAYER_MAX_SPEED);
		// if none of x movement keys are being pressed, slow down
		else if (player.velocity.x > 0)
			player.velocity.x = std::max<float>(player.velocity.x - (PLAYER_ACCEL_SPEED * delta_time), 0.0f);
		else if (player.velocity.x < 0)
			player.velocity.x = std::min<float>(player.velocity.x + (PLAYER_ACCEL_SPEED * delta_time), 0.0f);
	}
	else {
		// decrease x and y velocity since none of the movement keys are being pressed
		if (player.velocity.y > 0)
			player.velocity.y = std::max<float>(player.velocity.y - (PLAYER_ACCEL_SPEED * delta_time), 0.0f);
		else if (player.velocity.y < 0)
			player.velocity.y = std::min<float>(player.velocity.y + (PLAYER_ACCEL_SPEED * delta_time), 0.0f);
		if (player.velocity.x > 0)
			player.velocity.x = std::max<float>(player.velocity.x - (PLAYER_ACCEL_SPEED * delta_time), 0.0f);
		else if (player.velocity.x < 0)
			player.velocity.x = std::min<float>(player.velocity.x + (PLAYER_ACCEL_SPEED * delta_time), 0.0f);
	}

	player.update_position(delta_time);
}

void Engine::render_scene() {
	SDL_Rect pos;

	// render the background if set to a texture
	if (background_texture != nullptr) {
		int32_t transform_x = player.player_object.position.x - PLAYER_CENTER_X;
		int32_t transform_y = player.player_object.position.y - PLAYER_CENTER_Y;

		// make sure background_position always has coords for the top-right tile of the background
		// while still being visible on the screen

		if (background_position.y - transform_y > 0)
			background_position.y -= WINDOW_HEIGHT;
		else if (-(background_position.y - transform_y) > WINDOW_HEIGHT)
			background_position.y += WINDOW_HEIGHT;

		if (background_position.x - transform_x < 0)
			background_position.x += WINDOW_WIDTH;
		else if (background_position.x - transform_x > WINDOW_WIDTH)
			background_position.x -= WINDOW_WIDTH;
		
		pos.x = background_position.x - transform_x;
		pos.y = background_position.y - transform_y;
		pos.w = WINDOW_WIDTH;
		pos.h = WINDOW_HEIGHT;

		// draw top right
		SDL_RenderCopy(renderer, background_texture, nullptr, &pos);
		// draw bottom right
		pos.y += WINDOW_HEIGHT;
		SDL_RenderCopy(renderer, background_texture, nullptr, &pos);
		// draw bottom left
		pos.x -= WINDOW_WIDTH;
		SDL_RenderCopy(renderer, background_texture, nullptr, &pos);
		// draw top left
		pos.y -= WINDOW_HEIGHT;
		SDL_RenderCopy(renderer, background_texture, nullptr, &pos);
	}

	// render player at the center of the screen
	pos.x = PLAYER_CENTER_X;
	pos.y = PLAYER_CENTER_Y;
	pos.w = 16 * WINDOW_SCALE;
	pos.h = 16 * WINDOW_SCALE;
	SDL_RenderCopyEx(
	    renderer,
		player.player_object.texture,
		&player.player_object.current_frame,
		&pos,
		player.player_object.angle,
		nullptr,
		SDL_FLIP_NONE
	);
	SDL_RenderCopyEx(
	    renderer,
		player.arm_object.texture,
		&player.arm_object.current_frame,
		&pos,
		player.arm_object.angle,
		nullptr,
		SDL_FLIP_NONE
	);

	// display everything to screen
	SDL_RenderPresent(renderer);
}
