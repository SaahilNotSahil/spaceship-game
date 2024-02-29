#ifndef GAME_H
#define GAME_H

#include "constants.h"

enum State { WELCOME, START, PAUSED, END, GAMEOVER };

class Game {
public:
  State state = WELCOME;

  int backgroundSweep = top;
  int sweepSpeed = 2;
  int sweepCounter = 0;
  const int maxSweeps = 10;

  int score = 0;

  float progressBarWidth = 30.0f;
  float progressBarHeight = 150.0f;
  float progressHeight = 0.0f;

  float healthIndicatorWidth = 150.0f;
  float healthIndicatorHeight = 30.0f;
  float healthWidth = healthIndicatorWidth;

  float healthIndicatorRed = 0.0f;
  float healthIndicatorGreen = 1.0f;
  float healthIndicatorBlue = 0.0f;

  void welcome();
  void start();
  void pause();
  void resume();
  void end();
  void gameOver();
  void reset();

  void welcomeScreen();
  void pausedScreen();
  void gameOverScreen(bool won);

  void drawProgressBar();
  void updateProgressBar();

  void drawHealthIndicator();
  void updateHealthIndicator();
};

extern Game game;

#endif
