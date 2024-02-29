#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include "utils.h"

#define MAX_ASTEROIDS 15

struct Asteroid {
  float cx;
  float cy;
  int size;
  int speed;
  float m;
  float c;

  Vertex vertices[7];
};

void initAsteroids();
void initAsteroid(Asteroid *asteroid);
void drawAsteroids(int numAsteroids);
void drawAsteroid(Asteroid *asteroid);
void updateAsteroids(int numAsteroids);

#endif
