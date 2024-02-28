#ifndef GAME_H
#define GAME_H

class Game
{
public:
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

    void start();
    void end();

    void drawProgressBar();
    void updateProgressBar(int backgroundSweep, int sweepCounter);

    void drawHealthIndicator();
    void updateHealthIndicator();
};

extern Game game;

#endif