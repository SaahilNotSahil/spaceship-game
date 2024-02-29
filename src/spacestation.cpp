#include <GL/freeglut.h>
#include <cmath>
#include <cstdlib>
#include <iostream>

#include "asteroids.h"
#include "constants.h"
#include "game.h"
#include "spaceship.h"
#include "spacestation.h"
#include "utils.h"

void drawSpacestation() {
  // GLuint texture;
  // generateTexture(&texture, "./assets/spacestation_texture.jpg");

  // glEnable(GL_TEXTURE_2D);
  // glBindTexture(GL_TEXTURE_2D, texture);

  glBegin(GL_TRIANGLES);
  glColor3f(0.1f, 0.1f, 0.1f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex2f(left, top);
  glTexCoord2f(0.0f, 0.0f);
  glVertex2f(left, top - 100);
  glTexCoord2f(1.0f, 1.0f);
  glVertex2f(right, top);
  glEnd();

  glBegin(GL_TRIANGLES);
  glColor3f(0.1f, 0.1f, 0.1f);
  glTexCoord2f(0.0f, 0.0f);
  glVertex2f(left, top - 100);
  glTexCoord2f(1.0f, 0.0f);
  glVertex2f(right, top - 100);
  glTexCoord2f(1.0f, 1.0f);
  glVertex2f(right, top);
  glEnd();

  // glDisable(GL_TEXTURE_2D);
}

void updateSpacestation() {
  if (getSpaceshipPosition().y >= top - 100 &&
      game.sweepCounter >= game.maxSweeps) {
    std::cout << "You won!" << std::endl;
    std::cout << "Your score is " << game.score << std::endl;

    game.end();
  }
}
