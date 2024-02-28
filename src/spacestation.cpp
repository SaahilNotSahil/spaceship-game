#include <cmath>
#include <cstdlib>
#include <ctime>
#include <GL/freeglut.h>
#include <iostream>

#include "asteroids.h"
#include "constants.h"
#include "game.h"
#include "spaceship.h"
#include "spacestation.h"
#include "utils.h"

void drawSpacestation()
{
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(left, top);
    glVertex2f(left, top - 100);
    glVertex2f(right, top);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(left, top - 100);
    glVertex2f(right, top - 100);
    glVertex2f(right, top);
    glEnd();
}

void updateSpacestation()
{
    if (leftVertex().y >= top - 100 && game.sweepCounter >= game.maxSweeps)
    {
        std::cout << "You won!" << std::endl;
        std::cout << "Your score is " << game.score << std::endl;

        game.end();
    }
}
