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
	Engine engine;
	if (engine.init_window() != 0)
		return 1;

	SDL_Texture* player_texture = engine.load_texture("assets/player.png");
	SDL_Texture* crosshair_texture = engine.load_texture("assets/crosshair.png");
	SDL_Texture* bg_texture = engine.load_texture("assets/tileset.png");
	engine.init_textures(player_texture, crosshair_texture);
	engine.set_background_texture(bg_texture);
	/////////////////////////////////////////////////////////////////////

	// TEST
	engine.player.object.position = {-300, -300}; // temporarily set player position
	// manually place a few rectangles for performance testing
	engine.map_add_rectangle({100, 40}, 200, 100, 43707, true, 0, false);
	engine.map_add_rectangle({400, 80}, 400, 200, 11189470, true, 0, true);
	engine.map_add_rectangle({400, 80}, 100, 500, 16711680, true, 0, true);
	engine.map_add_rectangle({500, 280}, 500, 500, 0x112233, true, 0, false);
	engine.map_add_rectangle({2000, 280}, 500, 500, 0x112233, true, 0, false);
	engine.map_add_rectangle({4500, 280}, 500, 500, 0x112233, true, 0, false);
	for (int i = 0; i < 100; i++)
		engine.map_add_rectangle({(float_t)400+i*100, (float_t)i*150}, 70, 70, 0x254364, true, 0, i % 2 == 0 ? true : false);
	for (int i = 0; i < 100; i++)
		engine.map_add_rectangle({(float_t)200+i*100, (float_t)i*150}, 70, 70, 0x254364, true, 0, i % 2 == 0 ? true : false);
	for (int i = 0; i < 100; i++)
		engine.map_add_rectangle({(float_t)i*100, (float_t)i*150}, 70, 70, 0x254364, true, 0, i % 2 == 0 ? true : false);
	for (int i = 0; i < 100; i++)
		engine.map_add_rectangle({(float_t)-200+i*100, (float_t)i*150}, 70, 70, 0x254364, true, 0, i % 2 == 0 ? true : false);
	for (int i = 0; i < 100; i++)
		engine.map_add_rectangle({(float_t)-400+i*100, (float_t)i*150}, 70, 70, 0x254364, true, 0, i % 2 == 0 ? true : false);
	for (int i = 0; i < 100; i++)
		engine.map_add_rectangle({(float_t)600+i*100, (float_t)i*150}, 70, 70, 0x254364, true, 0, i % 2 == 0 ? true : false);
	for (int i = 0; i < 100; i++)
		engine.map_add_rectangle({(float_t)800+i*100, (float_t)i*150}, 70, 70, 0x254364, true, 0, i % 2 == 0 ? true : false);
	for (int i = 0; i < 100; i++)
		engine.map_add_rectangle({(float_t)1000+i*100, (float_t)i*150}, 70, 70, 0x254364, true, 0, i % 2 == 0 ? true : false);
	for (int i = 0; i < 100; i++)
		engine.map_add_rectangle({(float_t)300+i*100, (float_t)i*150}, 70, 70, 0x254364, true, 0, i % 2 == 0 ? true : false);
	for (int i = 0; i < 100; i++)
		engine.map_add_rectangle({(float_t)100+i*100, (float_t)i*150}, 70, 70, 0x254364, true, 0, i % 2 == 0 ? true : false);
	for (int i = 0; i < 100; i++)
		engine.map_add_rectangle({(float_t)-100+i*100, (float_t)i*150}, 70, 70, 0x254364, true, 0, i % 2 == 0 ? true : false);
	for (int i = 0; i < 100; i++)
		engine.map_add_rectangle({(float_t)-300+i*100, (float_t)i*150}, 70, 70, 0x254364, true, 0, i % 2 == 0 ? true : false);
	for (int i = 0; i < 100; i++)
		engine.map_add_rectangle({(float_t)-500+i*100, (float_t)i*150}, 70, 70, 0x254364, true, 0, i % 2 == 0 ? true : false);
	for (int i = 0; i < 100; i++)
		engine.map_add_rectangle({(float_t)500+i*100, (float_t)i*150}, 70, 70, 0x254364, true, 0, i % 2 == 0 ? true : false);
	for (int i = 0; i < 100; i++)
		engine.map_add_rectangle({(float_t)700+i*100, (float_t)i*150}, 70, 70, 0x254364, true, 0, i % 2 == 0 ? true : false);
	for (int i = 0; i < 100; i++)
		engine.map_add_rectangle({(float_t)900+i*100, (float_t)i*150}, 70, 70, 0x254364, true, 0, i % 2 == 0 ? true : false);


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
