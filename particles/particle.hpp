#include <SDL2/SDL.h>

#include "sdl_helper.h"

class Particle {
public:
  double x = 0;
  double y = 0;
  double vx = 100;
  double vy = 100;
  double radius = 5.0;
  double x_max = 320;
  double y_max = 160;

  Particle() {}

  Particle(double r0) { radius = r0; }

  void set(double x0, double y0, double vx0, double vy0) {
    x = x0;
    y = y0;
    vx = vx0;
    vy = vy0;
  };

  void update(double dt) {
    x += vx * dt;
    y += vy * dt;

    if (x - radius <= 0) {
      x = radius;
      vx = -vx;
    } else if (x + radius >= x_max) {
      x = x_max - radius;
      vx = -vx;
    }

    if (y - radius <= 0) {
      y = radius;
      vy = -vy;
    } else if (y + radius >= y_max) {
      y = y_max - radius;
      vy = -vy;
    }
  };

  void render(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderFillCircle(renderer, x, y, radius);
  }
};
