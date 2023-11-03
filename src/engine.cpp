#include "include/engine.h"

Engine::Engine() {
	SDL_ShowCursor(SDL_FALSE);
}

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
		//SDL_WINDOW_FULLSCREEN_DESKTOP
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

bool Engine::running() {
	return !quit;
}

void Engine::handle_events() {
	while (SDL_PollEvent(&e))
		if (e.type == SDL_QUIT)
			quit = true;
}

SDL_Texture* Engine::load_texture(const std::string& file_path) {
	SDL_Texture* t = nullptr;
	t = IMG_LoadTexture(renderer, file_path.c_str());
	if (t == nullptr)
		log_error(std::cout, "IMG_LoadTexture");
	return t;
}

void Engine::init_textures(SDL_Texture* player_texture, SDL_Texture* crosshair_texture_) {
	player.init_textures(player_texture);
	crosshair_texture = crosshair_texture_;
	crosshair_frame.w = 16;
	crosshair_frame.h = 16;
	crosshair_frame.x = 0;
	crosshair_frame.y = 0;
}

void Engine::set_background_texture(SDL_Texture* bg_texture) {
	background_texture = bg_texture;
	background_position = {0, 0};
}

bool Engine::check_collision(Object* obj1, Object* obj2) {
	// points for object 1's hitbox
	float_t obj1_top_left_x = obj1->position.x,
		obj1_top_left_y = obj1->position.y,
		obj1_bottom_right_x = obj1->position.x + obj1->current_frame.w,
		obj1_bottom_right_y = obj1->position.y + obj1->current_frame.h,
	// points for object 2's hitbox
		obj2_top_left_x = obj2->position.x,
		obj2_top_left_y = obj2->position.y,
		obj2_bottom_right_x = obj2->position.x + obj2->current_frame.w,
		obj2_bottom_right_y = obj2->position.y + obj2->current_frame.h;

	return ((
			 (obj1_top_left_x > obj2_top_left_x && obj1_top_left_x < obj2_bottom_right_x) ||
			 (obj1_bottom_right_x > obj2_top_left_x && obj1_bottom_right_x < obj2_bottom_right_x)
			) && (
			 (obj1_top_left_y > obj2_top_left_y && obj1_top_left_y < obj2_bottom_right_y) ||
			 (obj1_bottom_right_y > obj2_top_left_y && obj1_bottom_right_y < obj2_bottom_right_y)
		   ));
}

void Engine::render_object(Object* object) {
	SDL_Rect pos;
	float_t transform_x = player.object.position.x - PLAYER_CENTER_X;
	float_t transform_y = player.object.position.y - PLAYER_CENTER_Y;
	pos.x = object->position.x - transform_x;
	pos.y = object->position.y - transform_y;
	pos.w = object->current_frame.w;
	pos.h = object->current_frame.h;

	if (!(
		  (pos.x + pos.w <= 0) || (pos.x >= (int32_t) WINDOW_WIDTH) ||
		  (pos.y + pos.h <= 0) || (pos.y >= (int32_t) WINDOW_HEIGHT))
		) SDL_RenderCopyEx(renderer, object->texture, &object->current_frame, &pos, object->angle, nullptr, SDL_FLIP_NONE);
}

void Engine::update(float_t delta_time) {
	kbd_state = SDL_GetKeyboardState(nullptr);
	SDL_GetMouseState(&mouse_position.x, &mouse_position.y);

	// update plater velocity
	if (kbd_state[SDL_SCANCODE_W] || kbd_state[SDL_SCANCODE_A] || kbd_state[SDL_SCANCODE_S] || kbd_state[SDL_SCANCODE_D]) {
		// y movement
		if (kbd_state[SDL_SCANCODE_W])
			player.set_velocity_y(std::max<float>(player.get_velocity_y() - (PLAYER_ACCEL_SPEED * delta_time), -PLAYER_MAX_SPEED));
		else if (kbd_state[SDL_SCANCODE_S])
			player.set_velocity_y(std::min<float>(player.get_velocity_y() + (PLAYER_ACCEL_SPEED * delta_time), PLAYER_MAX_SPEED));
		// if none of y movement keys are being pressed, slow down
		else if (player.get_velocity_y() > 0)
			player.set_velocity_y(std::max<float>(player.get_velocity_y() - (PLAYER_ACCEL_SPEED * delta_time), 0.0f));
		else if (player.get_velocity_y() < 0)
			player.set_velocity_y(std::min<float>(player.get_velocity_y() + (PLAYER_ACCEL_SPEED * delta_time), 0.0f));

		// x movement
		if (kbd_state[SDL_SCANCODE_A])
			player.set_velocity_x(std::max<float>(player.get_velocity_x() - (PLAYER_ACCEL_SPEED * delta_time), -PLAYER_MAX_SPEED));
		else if (kbd_state[SDL_SCANCODE_D])
			player.set_velocity_x(std::min<float>(player.get_velocity_x() + (PLAYER_ACCEL_SPEED * delta_time), PLAYER_MAX_SPEED));
		// if none of x movement keys are being pressed, slow down
		else if (player.get_velocity_x() > 0)
			player.set_velocity_x(std::max<float>(player.get_velocity_x() - (PLAYER_ACCEL_SPEED * delta_time), 0.0f));
		else if (player.get_velocity_x() < 0)
			player.set_velocity_x(std::min<float>(player.get_velocity_x() + (PLAYER_ACCEL_SPEED * delta_time), 0.0f));
	}
	else {
		// decrease x and y velocity since none of the movement keys are being pressed
		if (player.get_velocity_y() > 0)
			player.set_velocity_y(std::max<float>(player.get_velocity_y() - (PLAYER_ACCEL_SPEED * delta_time), 0.0f));
		else if (player.get_velocity_y() < 0)
			player.set_velocity_y(std::min<float>(player.get_velocity_y() + (PLAYER_ACCEL_SPEED * delta_time), 0.0f));
		if (player.get_velocity_x() > 0)
			player.set_velocity_x(std::max<float>(player.get_velocity_x() - (PLAYER_ACCEL_SPEED * delta_time), 0.0f));
		else if (player.get_velocity_x() < 0)
			player.set_velocity_x(std::min<float>(player.get_velocity_x() + (PLAYER_ACCEL_SPEED * delta_time), 0.0f));
	}

	// update player animation
	if (player_animation_timer >= 0.10) {
		player.update_animation_frame(mouse_position, WINDOW_CENTER_X, WINDOW_CENTER_Y);
		player_animation_timer = 0;
	}
	else player_animation_timer += delta_time;

	// update player position and check for collisions
	player.object.update_position(delta_time);

	// check collision with map
	for (Object rect : map_rectangles) {
		if (!rect.collision) continue;
		if (check_collision(&player.object, &rect)) {
			player.object.position -= player.object.velocity * delta_time;
			player.object.velocity.x = 0;
			player.object.velocity.y = 0;
		}
	}
	
}

void Engine::render_scene() {
	SDL_RenderClear(renderer);
	SDL_Rect pos;

	// render the background if set to a texture
	if (background_texture != nullptr) {
		float_t transform_x = player.object.position.x - PLAYER_CENTER_X;
		float_t transform_y = player.object.position.y - PLAYER_CENTER_Y;

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

	// render map
	for (Object rect : map_rectangles)
		render_object(&rect);
	
	// render player at the center of the screen
	pos.x = PLAYER_CENTER_X;
	pos.y = PLAYER_CENTER_Y;
	pos.w = 48;
	pos.h = 48;
	SDL_RenderCopyEx(
	    renderer,
		player.object.texture,
		&player.object.current_frame,
		&pos,
		player.object.angle,
		nullptr,
		SDL_FLIP_NONE
	);

	// render crosshair at mouse position
	pos.x = mouse_position.x;
	pos.y = mouse_position.y;
	pos.w = 32;
	pos.h = 32;
	SDL_RenderCopyEx(
	    renderer,
		crosshair_texture,
		nullptr,
		&pos, 0, nullptr, SDL_FLIP_NONE
	);

	// display everything to screen
	SDL_RenderPresent(renderer);
}

void Engine::map_reset() {
	for (Object rect : map_rectangles)
		SDL_DestroyTexture(rect.texture);
	map_rectangles.clear();
}

void Engine::map_add_rectangle(Vec2<float_t> position, uint32_t width, uint32_t height, uint32_t color, bool filled, uint32_t border_width, bool collision) {
	Object rect;
	rect.texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
	rect.current_frame.x = 0;
	rect.current_frame.y = 0;
	rect.current_frame.w = width;
	rect.current_frame.h = height;
	rect.position = position;
	rect.collision = collision;

	uint32_t* pixels = (uint32_t*) malloc(width * height * sizeof(uint32_t));

	// TODO: 'filled' and 'border_width'
	// TODO: fix color so it will work
	for (uint32_t p = 0; p < (width * height); p++)
		pixels[p] = color;

	SDL_UpdateTexture(rect.texture, nullptr, pixels, width * sizeof(uint32_t));
	map_rectangles.push_back(rect);
}
