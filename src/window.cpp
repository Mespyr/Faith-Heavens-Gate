#include "include/window.h"

Window::Window(std::ostream &error_log_ostream, const char* name, uint32_t width, uint32_t height)
	: error_log_ostream(error_log_ostream),
	  WINDOW_WIDTH(width),
	  WINDOW_HEIGHT(height),
	  WINDOW_CENTER_X(width/2),
	  WINDOW_CENTER_Y(height/2) {

	window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		log_error(error_log_ostream, "SDL_CreateWindow");
		fail_init = true;
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		log_error(error_log_ostream, "SDL_CreateRenderer");
		fail_init = true;
		return;
	}
}

Window::~Window() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

uint32_t Window::width() {
	return WINDOW_WIDTH;
}

uint32_t Window::height() {
	return WINDOW_HEIGHT;
}

uint32_t Window::center_x() {
	return WINDOW_CENTER_X;
}

uint32_t Window::center_y() {
	return WINDOW_CENTER_Y;
}

SDL_Texture* Window::load_texture(const char* file_path) {
	SDL_Texture* t = nullptr;
	t = IMG_LoadTexture(renderer, file_path);
	if (t == nullptr)
		log_error(error_log_ostream, "IMG_LoadTexture");
	return t;
}

SDL_Texture* Window::create_texture(uint32_t width, uint32_t height) {
	return SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, width, height);
}

void Window::render_texture(SDL_Texture* texture, SDL_Rect* frame, SDL_Rect* position) {
	SDL_RenderCopyEx(renderer, texture, frame, position, 0, nullptr, SDL_FLIP_NONE);
}

void Window::clear() {
	SDL_RenderClear(renderer);
}

void Window::present() {
	SDL_RenderPresent(renderer);
}
