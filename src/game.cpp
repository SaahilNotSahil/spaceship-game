#include <cmath>
#include <cstdlib>
#include <ctime>
#include <GL/freeglut.h>
#include <iostream>

#include "constants.h"
#include "game.h"
#include "spaceship.h"

void Game::start()
{
    std::cout << "Game started!" << std::endl;
}

void Game::end()
{
    std::cout << "Game ended!" << std::endl;

    exit(0);
}

void Game::drawProgressBar()
{
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
    glVertex2f(right - progressBarWidth - 50, progressHeight - progressBarHeight / 2);
    glEnd();
}

void Game::updateProgressBar(int backgroundSweep, int sweepCounter)
{
    progressHeight = ((float)sweepCounter + (top - backgroundSweep) / (float)windowHeight) * progressBarHeight / 10.0f;
    if (progressHeight >= progressBarHeight)
    {
        progressHeight = progressBarHeight;
    }
}

void Game::drawHealthIndicator()
{
    glColor4f(1.0f, 1.0f, 1.0f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(left + 50, top - healthIndicatorHeight - 50);
    glVertex2f(left + healthIndicatorWidth + 50, top - healthIndicatorHeight - 50);
    glVertex2f(left + healthIndicatorWidth + 50, top - 50);
    glVertex2f(left + 50, top - 50);
    glEnd();

    glColor4f(healthIndicatorRed, healthIndicatorGreen, healthIndicatorBlue, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(left + 50, top - healthIndicatorHeight - 50);
    glVertex2f(left + healthWidth + 50, top - healthIndicatorHeight - 50);
    glVertex2f(left + healthWidth + 50, top - 50);
    glVertex2f(left + 50, top - 50);
    glEnd();
}

void Game::updateHealthIndicator()
{
    healthWidth = (health() / 100.0f) * healthIndicatorWidth;
    if (healthWidth <= left + 50)
    {
        healthWidth = left + 50;
    }

    healthIndicatorRed = 1.0f - (health() / 100.0f);
    if (healthIndicatorRed < 0.0f)
    {
        healthIndicatorRed = 0.0f;
    }

    healthIndicatorGreen = health() / 100.0f;
    if (healthIndicatorGreen > 1.0f)
    {
        healthIndicatorGreen = 1.0f;
    }
}

Game game = Game();
