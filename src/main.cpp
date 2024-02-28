#include <cmath>
#include <cstdlib>
#include <ctime>
#include <GL/freeglut.h>
#include <iostream>

#include "asteroids.h"
#include "background.h"
#include "constants.h"
#include "game.h"
#include "spaceship.h"
#include "spacestation.h"

int backgroundSweep = top;
int sweepSpeed = 2;
int sweepCounter = 0;

bool upPressed = false;
bool downPressed = false;
bool leftPressed = false;
bool rightPressed = false;

void resize(int, int height);
void init();
void display();
void timer(int);
void handleKeyboardInput(unsigned char key, int x, int y);
void specialKeyPressed(int key, int x, int y);
void specialKeyReleased(int key, int x, int y);

int main(int argc, char **argv)
{
    srand(time(nullptr));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Spaceship Game");
    glutReshapeFunc(resize);

    init();

    game.start();

    initStars();
    initAsteroids();
    initSpaceship();

    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeyboardInput);
    glutSpecialFunc(specialKeyPressed);
    glutSpecialUpFunc(specialKeyReleased);
    glutTimerFunc(16, timer, 0);
    glutMainLoop();

    return 0;
}

void resize(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // gluOrtho2D(-1000, 1000, -1000, 1000);
    gluOrtho2D(left, right, bottom, top);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void init()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawStars();
    drawAsteroids(5);
    drawSpaceship();
    game.drawProgressBar();
    game.drawHealthIndicator();

    if (sweepCounter >= 10)
    {
        drawSpacestation();
    }

    glFlush();
}

void timer(int)
{
    backgroundSweep -= sweepSpeed;

    if (backgroundSweep < bottom)
    {
        backgroundSweep = top;
        sweepCounter++;
    }

    updateStars();
    updateAsteroids(5);

    game.updateProgressBar(backgroundSweep, sweepCounter);
    game.updateHealthIndicator();

    updateSpacestation(sweepCounter);

    if (health() <= 0)
    {
        std::cout << "GAME OVER" << std::endl;
        std::cout << "SCORE: " << game.score << std::endl;

        exit(1);
    }

    if (upPressed && leftPressed)
    {
        moveUp();
        moveLeft();
    }
    else if (upPressed && rightPressed)
    {
        moveUp();
        moveRight();
    }
    else if (upPressed && downPressed)
    {
    }
    else if (leftPressed && rightPressed)
    {
    }
    else if (downPressed && leftPressed)
    {
        moveDown();
        moveLeft();
    }
    else if (downPressed && rightPressed)
    {
        moveDown();
        moveRight();
    }
    else if (upPressed)
    {
        moveUp();
    }
    else if (downPressed)
    {
        moveDown();
    }
    else if (leftPressed)
    {
        moveLeft();
    }
    else if (rightPressed)
    {
        moveRight();
    }

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void handleKeyboardInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'q':
        exit(0);
        break;
    }
}

void specialKeyPressed(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        upPressed = true;
        break;
    case GLUT_KEY_DOWN:
        downPressed = true;
        break;
    case GLUT_KEY_LEFT:
        leftPressed = true;
        break;
    case GLUT_KEY_RIGHT:
        rightPressed = true;
        break;
    }
}

void specialKeyReleased(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        upPressed = false;

        break;
    case GLUT_KEY_DOWN:
        downPressed = false;

        break;
    case GLUT_KEY_LEFT:
        leftPressed = false;

        break;
    case GLUT_KEY_RIGHT:
        rightPressed = false;

        break;
    }
}
