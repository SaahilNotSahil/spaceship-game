#include <GL/freeglut.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "asteroids.h"
#include "background.h"
#include "constants.h"
#include "game.h"
#include "spaceship.h"
#include "utils.h"

void Game::welcome() {
  state = WELCOME;

  initStars();
  initAsteroids();
  initSpaceship();
}

void Game::start() {
  std::cout << "Game started!" << std::endl;

  state = START;
}

void Game::pause() {
  std::cout << "Game paused!" << std::endl;

  state = PAUSED;
}

void Game::resume() {
  std::cout << "Game resumed!" << std::endl;

  state = START;
}

void Game::end() {
  std::cout << "Game ended!" << std::endl;

  state = END;
}

void Game::gameOver() {
  std::cout << "Game over!" << std::endl;
  std::cout << "Score: " << score << std::endl;

  state = GAMEOVER;
}

void Game::reset() {
  state = WELCOME;

  backgroundSweep = top;
  sweepSpeed = 2;
  sweepCounter = 0;

  score = 0;

  progressBarWidth = 30.0f;
  progressBarHeight = 150.0f;
  progressHeight = 0.0f;

  healthIndicatorWidth = 150.0f;
  healthIndicatorHeight = 30.0f;
  healthWidth = healthIndicatorWidth;

  healthIndicatorRed = 0.0f;
  healthIndicatorGreen = 1.0f;
  healthIndicatorBlue = 0.0f;

  welcome();
}

void Game::welcomeScreen() {
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  glRasterPos2f(-100.0f, 20.0f);
  Write((char *)"Welcome to Spaceship Game!");
  glRasterPos2f(-80.0f, -20.0f);
  Write((char *)"Press 's' to start the game.");
  glRasterPos2f(-120.0f, -60.0f);
  Write((char *)"Press 'p' to pause/resume the game.");
  glRasterPos2f(-80.0f, -100.0f);
  Write((char *)"Press 'q' to quit the game.");
}

void Game::pausedScreen() {
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  glRasterPos2f(-50.0f, 20.0f);
  Write((char *)"Game paused!");
  glRasterPos2f(-100.0f, -20.0f);
  Write((char *)"Press 'p' to resume the game.");
}

void Game::gameOverScreen(bool won) {
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

  if (won) {
    glRasterPos2f(-100.0f, 20.0f);
    Write((char *)"Congratulations! You won!");
    char buffer[100];
    sprintf(buffer, "Score: %d", score);
    glRasterPos2f(-90.0f, -20.0f);
    Write(buffer);
    glRasterPos2f(-90.0f, -60.0f);
    Write((char *)"Press 'r' to restart the game.");
    glRasterPos2f(-90.0f, -100.0f);
    Write((char *)"Press 'q' to quit the game.");
  } else {
    glRasterPos2f(-100.0f, 20.0f);
    Write((char *)"Game over! You lost all your health.");
    char buffer[100];
    sprintf(buffer, "Score: %d", score);
    glRasterPos2f(-90.0f, -20.0f);
    Write(buffer);
    glRasterPos2f(-90.0f, -60.0f);
    Write((char *)"Press 'r' to restart the game.");
    glRasterPos2f(-90.0f, -100.0f);
    Write((char *)"Press 'q' to quit the game.");
  }
}

void Game::drawProgressBar() {
  glColor4f(1.0f, 1.0f, 1.0f, 0.2f);
  glBegin(GL_QUADS);
  glVertex2f(right - progressBarWidth - 50, -progressBarHeight / 2);
  glVertex2f(right - 50, -progressBarHeight / 2);
  glVertex2f(right - 50, progressBarHeight / 2);
  glVertex2f(right - progressBarWidth - 50, progressBarHeight / 2);
  glEnd();

  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  glBegin(GL_QUADS);
  glVertex2f(right - progressBarWidth - 50, -progressBarHeight / 2);
  glVertex2f(right - 50, -progressBarHeight / 2);
  glVertex2f(right - 50, progressHeight - progressBarHeight / 2);
  glVertex2f(right - progressBarWidth - 50,
             progressHeight - progressBarHeight / 2);
  glEnd();
}

void Game::updateProgressBar() {
  progressHeight =
      ((float)sweepCounter + (top - backgroundSweep) / (float)windowHeight) *
      progressBarHeight / (float)maxSweeps;
  if (progressHeight >= progressBarHeight) {
    progressHeight = progressBarHeight;
  }
}

void Game::drawHealthIndicator() {
  glColor4f(1.0f, 1.0f, 1.0f, 0.2f);
  glBegin(GL_QUADS);
  glVertex2f(left + 50, top - healthIndicatorHeight - 125);
  glVertex2f(left + healthIndicatorWidth + 50,
             top - healthIndicatorHeight - 125);
  glVertex2f(left + healthIndicatorWidth + 50, top - 125);
  glVertex2f(left + 50, top - 125);
  glEnd();

  glColor4f(healthIndicatorRed, healthIndicatorGreen, healthIndicatorBlue,
            1.0f);
  glBegin(GL_QUADS);
  glVertex2f(left + 50, top - healthIndicatorHeight - 125);
  glVertex2f(left + healthWidth + 50, top - healthIndicatorHeight - 125);
  glVertex2f(left + healthWidth + 50, top - 125);
  glVertex2f(left + 50, top - 125);
  glEnd();

  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  glRasterPos2f(left + healthIndicatorWidth / 2.0f + 20, top - 147.5);
  Write((char *)"HEALTH");
}

void Game::updateHealthIndicator() {
  healthWidth = (health() / 100.0f) * healthIndicatorWidth;
  if (healthWidth <= left + 50) {
    healthWidth = left + 50;
  }

  healthIndicatorRed = 1.0f - (health() / 100.0f);
  if (healthIndicatorRed < 0.0f) {
    healthIndicatorRed = 0.0f;
  }

  healthIndicatorGreen = health() / 100.0f;
  if (healthIndicatorGreen > 1.0f) {
    healthIndicatorGreen = 1.0f;
  }
}

Game game = Game();
