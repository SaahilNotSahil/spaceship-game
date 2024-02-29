#include <GL/freeglut.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "asteroids.h"
#include "constants.h"
#include "game.h"
#include "spaceship.h"
#include "utils.h"

Asteroid asteroids[MAX_ASTEROIDS];

void calculateVertices(Asteroid *asteroid) {
  float angle = 0.0f;
  for (int i = 0; i < 7; i++) {
    asteroid->vertices[i].x = asteroid->cx + asteroid->size * cos(angle);
    asteroid->vertices[i].y = asteroid->cy + asteroid->size * sin(angle);
    angle += 2 * M_PI / 7;
  }
}

void initAsteroids() {
  for (int i = 0; i < MAX_ASTEROIDS; i++) {
    initAsteroid(&asteroids[i]);
  }
}

void initAsteroid(Asteroid *asteroid) {
  int pos_or_neg = randint(0, 1);

  if (pos_or_neg == 0) {
    asteroid->cx = randint(-600, -400);
  } else {
    asteroid->cx = randint(400, 600);
  }

  asteroid->size = randint(20, 60);
  asteroid->c = randint(-300, 300);

  if (asteroid->cx > 0) {
    asteroid->m = (float)randint(int((-300 - asteroid->c) / asteroid->cx),
                                 int((300 - asteroid->c) / asteroid->cx));
  } else {
    asteroid->m = (float)randint(int((300 - asteroid->c) / asteroid->cx),
                                 int((-300 - asteroid->c) / asteroid->cx));
  }

  if (asteroid->m < 0) {
    asteroid->speed = randint(4, 7);
  } else {
    asteroid->speed = randint(-7, -4);
  }

  asteroid->cy = asteroid->m * asteroid->cx + asteroid->c;

  calculateVertices(asteroid);
}

void drawAsteroids(int numAsteroids) {
  for (int i = 0; i < numAsteroids; i++) {
    drawAsteroid(&asteroids[i]);
  }
}

void drawAsteroid(Asteroid *asteroid) {
  glBegin(GL_POLYGON);
  glColor3f(0.325f, 0.274f, 0.258f);
  for (int i = 0; i < 7; i++) {
    glVertex2f(asteroid->vertices[i].x, asteroid->vertices[i].y);
  }
  glEnd();
}

void updateAsteroids(int numAsteroids) {
  for (int i = 0; i < numAsteroids; i++) {
    Vertex spaceshipPosition = getSpaceshipPosition();
    Vertex *asteroidPosition = (Vertex *)malloc(sizeof(Vertex));
    asteroidPosition->x = asteroids[i].cx;
    asteroidPosition->y = asteroids[i].cy;

    float distance = euclidean_distance(spaceshipPosition, *asteroidPosition);
    float collisionDistance = collisionRadius() + asteroids[i].size;

    if (distance < collisionDistance) {
      collide(asteroids[i].size);
      initAsteroid(&asteroids[i]);

      break;
    }

    asteroids[i].cx += asteroids[i].speed / sqrt(pow(asteroids[i].m, 2) + 1);
    asteroids[i].cy = asteroids[i].m * asteroids[i].cx + asteroids[i].c;

    calculateVertices(&asteroids[i]);

    if (asteroids[i].cy < -300 || asteroids[i].cx > 600 ||
        asteroids[i].cx < -600) {
      game.score += asteroids[i].size / 5;

      initAsteroid(&asteroids[i]);
    }
  }
}
