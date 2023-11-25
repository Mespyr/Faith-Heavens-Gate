#include <SDL2/SDL_render.h>
#include <cstdint>
#include <iostream>
#include <SDL2/SDL.h>

#include "include/util.h"
#include "include/engine.h"
#include "include/object.h"
#include "include/vec2.h"

int32_t main() {
	if (init_lib() != 0)
		return 1;

	////////////////// initialize engine and textures ///////////////////
	Engine engine(std::cerr, "Pants", 1920, 1080);
	if (engine.fail_init)
		return 1;

	SDL_Texture* player_texture = engine.window.load_texture("assets/player.png");
	SDL_Texture* crosshair_texture = engine.window.load_texture("assets/crosshair.png");
	SDL_Texture* bg_texture = engine.window.load_texture("assets/tileset.png");
	engine.init_textures(player_texture, crosshair_texture);
	/////////////////////////////////////////////////////////////////////

	// TEST
	engine.set_background_texture(bg_texture);
	engine.player.object.position = {352, 400}; // temporarily set player position
	// manually place a few rectangles for performance testing
	//engine.map_add_rectangle({-500, -500}, 200, 200, 0x3c3c3c, false, 5, 0x191919);
	//engine.map_add_rectangle({-200, -200}, 20, 20, 0x2e2e2e, true, 3, 0x191919);
	//engine.map_add_rectangle({100, 40}, 200, 100, 0xA164C8, false, 0);
	//engine.map_add_rectangle({400, 80}, 400, 200, 0x646464, true, 0);
	//engine.map_add_rectangle({400, 80}, 100, 500, 0xA164C8, true, 0);
	//engine.map_add_rectangle({500, 280}, 500, 500, 0x646464, false, 0);
	//engine.map_add_rectangle({2000, 280}, 500, 500, 0xA164c8, false, 0);
	//engine.map_add_rectangle({4500, 280}, 500, 500, 0x646464, false, 0);

	//for (int x = 1; x <= 200; x++) {
	//	for (int i = 0; i < 100; i++) {
	//		engine.map_add_rectangle({(float_t)(x*100)+i*100, (float_t)i*150}, 70, 70, 0x323232, i % 2 == 0 ? false: true, 5);
	//		engine.map_add_rectangle({(float_t)(-x*100)+i*100, (float_t)i*150}, 70, 70, 0x131313, i % 2 == 0 ? false: true, 5);
	//	}
	//}

	engine.map_add_rectangle({0, 0}, 800, 1200, 0x333333, false);
	engine.map_add_rectangle({0, 0}, 800, 10, 0x000000, true);
	engine.map_add_rectangle({0, 0}, 10, 1200, 0x000000, true);
	engine.map_add_rectangle({790, 0}, 10, 1200, 0x000000, true);
	engine.map_add_rectangle({0, 1190}, 300, 10, 0x000000, true);
	engine.map_add_rectangle({500, 1190}, 300, 10, 0x000000, true);
	engine.map_add_rectangle({200, 200}, 200, 200, 0x000000, true, 20, 0xFFFFFF);
	
	uint32_t now, last_game_step = SDL_GetTicks();
	float_t delta_time;

	// game loop
	while (engine.running()) {
		now = SDL_GetTicks();
		engine.handle_events();
		if (last_game_step < now) {
			delta_time = (now - last_game_step) / 1000.0f;
			engine.update(delta_time);
			engine.render_scene();
		}
		else SDL_Delay(1);
		last_game_step = now;
	}

	engine.map_reset();
	SDL_DestroyTexture(player_texture);
	SDL_DestroyTexture(crosshair_texture);
	SDL_DestroyTexture(bg_texture);
	SDL_Quit();
	return 0;
}
