#include <random>
#include <vector>

#include "particle.hpp"

#define NUM_PARTICLES 50

class ParticlesManager {
private:
  std::vector<Particle> particles;

public:
  ParticlesManager(double v_max = 100) {
    particles.resize(NUM_PARTICLES);

    std::random_device seed_gen;
    std::default_random_engine engine(seed_gen());

    std::uniform_real_distribution<> xrand(0.0, 320.0), yrand(0.0, 160.0),
        vrand(-v_max, v_max);
    std::normal_distribution<> rrand(5.0, 2.0);

    for (int i = 0; i < NUM_PARTICLES; i++) {
      double x0 = xrand(engine);
      double y0 = yrand(engine);
      double vx0 = vrand(engine);
      double vy0 = vrand(engine);
      double r = abs(rrand(engine));

      particles[i] = Particle(r);
      particles[i].set(x0, y0, vx0, vy0);
    }
  }

  void update_all(double dt) {
    for (auto &p : particles) {
      p.update(dt);
    }
    calculate_bounding();
  }

  void render_all(SDL_Renderer *renderer) {
    for (auto p : particles) {
      p.render(renderer);
    }
  }

  void calculate_bounding() {
    for (int l = 0; l < NUM_PARTICLES; l++) {
      for (int r = l + 1; r < NUM_PARTICLES; r++) {
        auto &pl = particles[l];
        auto &pr = particles[r];

        double dx = pl.x - pr.x;
        double dy = pl.y - pr.y;
        double sum_of_radii = pl.radius + pr.radius;
        if (dx * dx + dy * dy <= sum_of_radii * sum_of_radii &&
            will_intersect(pl, pr)) {
          // Swap velocity vectors
          double plvx = pl.vx;
          double plvy = pl.vy;
          pl.vx = pr.vx;
          pl.vy = pr.vy;
          pr.vx = plvx;
          pr.vy = plvy;
        }
      }
    }
  }

  // https://qiita.com/zu_rin/items/e04fdec4e3dec6072104
  bool will_intersect(Particle l, Particle r) {
    double dt = 5;

    double dax = l.vx * dt;
    double day = l.vy * dt;

    double r2x = r.x + r.vx * dt;
    double r2y = r.y + r.vy * dt;

    double s = dax * (r.y - l.y) - day * (r.x - l.x);
    double t = dax * (r2y - l.y) - day * (r2x - l.x);

    return s * t < 0;
  }
};
