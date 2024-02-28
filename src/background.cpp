#include <ctime>
#include <GL/freeglut.h>

#include "background.h"
#include "constants.h"

struct Star
{
    int x;
    int y;
};

Star stars[numStars];

void initStars()
{
    for (int i = 0; i < numStars; ++i)
    {
        stars[i].x = rand() % 800 + left;
        stars[i].y = rand() % windowHeight + bottom;
    }
}

void drawStars()
{
    for (int i = 0; i < numStars; ++i)
    {
        drawStar(stars[i].x, stars[i].y);
    }
}

void drawStar(int x, int y)
{
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void updateStars()
{
    for (int i = 0; i < numStars; ++i)
    {
        stars[i].y = (stars[i].y - starSpeed);

        if (stars[i].y == bottom)
        {
            stars[i].y = top;
        }
    }
}
