#include <cstdint>
#include <iostream>
#include <SDL2/SDL.h>

#include "include/util.h"
#include "include/engine.h"
#include "include/object.h"

int32_t main() {
	if (init_lib() != 0)
		return 1;

	Engine engine;
	if (engine.init() != 0)
		return 1;

	bool quit = false;
	SDL_Event e;
	uint32_t now, last_game_step = SDL_GetTicks();
	float delta_time;

	// create an object to draw on the screen
	SDL_Texture* man_tex = engine.load_texture("assets/player.png");
	Object man_obj(608, 328, man_tex);
	man_obj.current_frame.x = 0;
	man_obj.current_frame.y = 0;
	man_obj.current_frame.w = 16;
	man_obj.current_frame.h = 16;
	
	while (!quit) {
		now = SDL_GetTicks();

		while (SDL_PollEvent(&e))
			if (e.type == SDL_QUIT)
				quit = true;

		if (last_game_step < now) {
			delta_time = (now - last_game_step) / 1000.0f;
			engine.clear();
			engine.render(man_obj, 4);
			engine.display();
		}
		else SDL_Delay(1);
		last_game_step = now;
	}
	
	SDL_Quit();
	return 0;
}
