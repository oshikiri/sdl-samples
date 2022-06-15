// Document: http://oshikiri.org/projects/sdl-samples/#particles

#include <stdbool.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <emscripten.h>

#include "particles_manager.hpp"

#define CANVAS_WIDTH 320
#define CANVAS_HEIGHT 160

int current_frame = 0;
Uint32 last_time;
Uint32 current_time;
Uint32 ms_per_frame = 10; // animate at 10 fps

SDL_Window *window;
SDL_Renderer *renderer;

bool paused = false;
SDL_Event event;
ParticlesManager particlesManager;

void poll_key_event() {
  if (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_KEYUP:
      switch (event.key.keysym.sym) {
      case SDLK_SPACE:
        paused = !paused;
        break;
      default:
        break;
      }
      break;

    default:
      break;
    }
  }
}

void show_animation() {
  poll_key_event();

  if (paused) {
    return;
  }

  current_time = SDL_GetTicks();

  Uint32 dt_ms = current_time - last_time;
  if (dt_ms >= ms_per_frame) {
    last_time = current_time;
  }
  double dt = (double)dt_ms / 1000.0;

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
  particlesManager.update_all(dt);
  particlesManager.render_all(renderer);
  SDL_RenderPresent(renderer);
}

int main() {
  SDL_Init(SDL_INIT_VIDEO);

  SDL_CreateWindowAndRenderer(CANVAS_WIDTH, CANVAS_HEIGHT, 0, &window,
                              &renderer);

  last_time = SDL_GetTicks();
  emscripten_set_main_loop(show_animation, 0, 0);

  return EXIT_SUCCESS;
}
