#include <stdbool.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <emscripten.h>

#include "sdl_extra.h"

#define PI 3.141592

#define FONT_FILE "font/Roboto-Black.ttf"
#define FONT_SIZE 32
#define CANVAS_WIDTH 320
#define CANVAS_HEIGHT 160

#define FRAME_COUNT 100

int current_frame = 0;
Uint32 last_time;
Uint32 current_time;
Uint32 ms_per_frame = 10; // animate at 10 fps

SDL_Window *window;
SDL_Renderer *renderer;

TTF_Font *font;
SDL_Rect dest = {.x = 0, .y = 0, .w = 0, .h = 0};
SDL_Color font_color = {255, 255, 255, 255}; // WHITE COLOR

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

void render_clock(SDL_Renderer *renderer, int minute) {
  minute %= 720;

  int m = minute % 60;
  int h = minute / 60;

  // Render HH:MM
  char s[6];
  sprintf(s, "%02d:%02d", h, m);
  SDL_Surface *temp_surface = TTF_RenderText_Blended(font, s, font_color);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, temp_surface);

  SDL_FreeSurface(temp_surface);
  SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
  SDL_RenderCopy(renderer, texture, NULL, &dest);

  // Render clock
  double xc = CANVAS_WIDTH / 2;
  double yc = CANVAS_HEIGHT / 2;
  double radius = CANVAS_HEIGHT / 2;

  // long hand
  double xl = xc + 0.9 * radius * sin(2 * PI * m / 60.0);
  double yl = yc - 0.9 * radius * cos(2 * PI * m / 60.0);

  // short hand
  double xs = xc + 0.6 * radius * sin(2 * PI * minute / 720.0);
  double ys = yc - 0.6 * radius * cos(2 * PI * minute / 720.0);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
  SDL_RenderDrawLine(renderer, xc, yc, xl, yl);
  SDL_RenderDrawLine(renderer, xc, yc, xs, ys);
  SDL_RenderDrawCircle(renderer, xc, yc, radius);
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
  current_frame %= 720;

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
  render_clock(renderer, current_frame);
  SDL_RenderPresent(renderer);
}

int main() {
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();

  font = TTF_OpenFont(FONT_FILE, FONT_SIZE);

  SDL_CreateWindowAndRenderer(CANVAS_WIDTH, CANVAS_HEIGHT, 0, &window,
                              &renderer);

  last_time = SDL_GetTicks();
  emscripten_set_main_loop(show_animation, 0, 0);

  return EXIT_SUCCESS;
}
