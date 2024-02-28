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
    game.welcome();

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

    if (game.state == WELCOME)
    {
        game.welcomeScreen();

        glutSwapBuffers();

        return;
    }
    else if (game.state == PAUSED)
    {
        game.pausedScreen();

        glutSwapBuffers();

        return;
    }
    else if (game.state == END)
    {
        game.gameOverScreen(true);

        glutSwapBuffers();

        return;
    }
    else if (game.state == GAMEOVER)
    {
        game.gameOverScreen(false);

        glutSwapBuffers();

        return;
    }

    drawStars();
    drawAsteroids(5);
    drawSpaceship();

    char buffer[15];

    sprintf(buffer, "Score: %d", game.score);

    glRasterPos2f(left + 75, top - 175);
    Write(buffer);

    if (game.sweepCounter >= game.maxSweeps)
    {
        drawSpacestation();
    }

    game.drawProgressBar();
    game.drawHealthIndicator();

    glFlush();
}

void timer(int)
{
    if (game.state != START)
    {
        glutPostRedisplay();
        glutTimerFunc(16, timer, 0);

        return;
    }

    game.backgroundSweep -= game.sweepSpeed;

    if (game.backgroundSweep < bottom)
    {
        game.backgroundSweep = top;
        game.sweepCounter++;
    }

    updateStars();
    updateAsteroids(5);

    game.updateProgressBar();
    game.updateHealthIndicator();

    if (health() <= 0)
    {
        game.gameOver();
    }

    updateSpacestation();

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
    case 's':
        if (game.state == WELCOME)
        {
            game.start();
        }

        break;
    case 'p':
        if (game.state == START)
        {
            game.pause();
        }
        else if (game.state == PAUSED)
        {
            game.resume();
        }

        break;
    case 'r':
        if (game.state == END || game.state == GAMEOVER)
        {
            game.reset();
        }

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
