
#include <stdbool.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <emscripten.h>

#include "sdl_helper.h"

#define PI 3.141592
#define GRAVITATIONAL_ACCELERATION 9.80665

#define CANVAS_WIDTH 320
#define CANVAS_HEIGHT 160
#define PENDULUM_RADIUS 10

#define FRAME_COUNT 100

int current_frame = 0;
Uint32 last_time;
Uint32 current_time;
Uint32 ms_per_frame = 10; // animate at 10 fps

SDL_Window *window;
SDL_Renderer *renderer;

bool paused = false;
SDL_Event event;

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

double step_size = 0.1;
double x1 = 2.0 * PI / 16.0; // theta
double x2 = 0;               // dot theta

void update(double *x1_prev, double *x2_prev, double duration, double length) {
  double dx1 = *x2_prev;
  double dx2 = -GRAVITATIONAL_ACCELERATION * sin(*x1_prev) / length;

  *x1_prev += step_size * dx1;
  *x2_prev += step_size * dx2;
}

void render_pendulum(SDL_Renderer *renderer, double length, double theta) {
  double x = CANVAS_WIDTH / 2.0 + length * sin(theta);
  double y = length * cos(theta);

  double xc = CANVAS_WIDTH / 2;
  double yc = 0;

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
  SDL_RenderDrawLine(renderer, xc, yc, x, y);
  SDL_RenderFillCircle(renderer, x, y, PENDULUM_RADIUS);
}

void show_animation() {
  poll_key_event();

  if (paused) {
    return;
  }

  current_time = SDL_GetTicks();

  int ms = current_time - last_time;
  if (ms >= ms_per_frame) {
    ++current_frame;
    last_time = current_time;
  }

  double pendulum_length = 150.0;
  double duration = 1.0 * current_frame / FRAME_COUNT;
  update(&x1, &x2, duration, pendulum_length);
  // printf("duration=%f, x1=%f, x2=%f, theta=%f\n", duration, x1, x2, theta);

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
  render_pendulum(renderer, pendulum_length, x1);
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
