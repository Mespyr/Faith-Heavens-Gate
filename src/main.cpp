#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

#include <cstdint>
#include <iostream>

#include "include/engine.h"
#include "include/object.h"
#include "include/util.h"
#include "include/vec2.h"

int32_t main() {
    if (init_lib() != 0) return 1;

    ////////////////// initialize engine and textures ///////////////////
    Window window(std::cerr, "Pants", 1920, 1080);
    if (window.fail_init) return 1;

    Engine engine(std::cerr);
    if (engine.fail_init) return 1;

    engine.set_window(&window);

    SDL_Texture* player_texture = window.load_texture("assets/player.png");
    SDL_Texture* crosshair_texture =
        window.load_texture("assets/crosshair.png");
    SDL_Texture* bg_texture = window.load_texture("assets/tileset.png");
    engine.init_textures(player_texture, crosshair_texture);
    /////////////////////////////////////////////////////////////////////

    // TEST
    engine.set_player_position({352, 400});
    engine.set_background_texture(bg_texture);
    engine.map_add_rectangle({500, 100}, 200, 500, 0x777777, true, 3, 0x333333);
    engine.map_add_rectangle({500, 600}, 200, 40, 0x333333, false, 0);
    engine.map_add_rectangle({200, 500}, 200, 100, 0x777777, true, 3, 0x333333);
    engine.map_add_rectangle({200, 600}, 200, 40, 0x333333, false, 0);

    uint32_t now, last_game_step = SDL_GetTicks();
    float_t  delta_time;

    // game loop
    while (engine.running()) {
        now = SDL_GetTicks();
        engine.handle_events();
        if (last_game_step < now) {
            delta_time = (now - last_game_step) / 1000.0f;
            engine.update(delta_time);
            engine.render_scene();
        } else
            SDL_Delay(1);
        last_game_step = now;
    }

    engine.map_reset();
    SDL_DestroyTexture(player_texture);
    SDL_DestroyTexture(crosshair_texture);
    SDL_DestroyTexture(bg_texture);
    SDL_Quit();
    return 0;
}
