#include <cmath>
#include <cstdlib>
#include <GL/freeglut.h>
#include <iostream>

#include "spaceship.h"
#include "utils.h"

Spaceship *spaceship = (Spaceship *)malloc(sizeof(Spaceship));

void initSpaceship()
{
    spaceship->cx = 0.0f;
    spaceship->cy = -300.0f + float(50 / (2 * sqrt(3)));
    spaceship->length = 125;
    spaceship->speed = 5;
    spaceship->health = 100.0f;
}

Vertex leftVertex()
{
    Vertex v;
    v.x = spaceship->cx - float(spaceship->length / 2);
    v.y = spaceship->cy - float(spaceship->length / (2 * sqrt(3)));
    return v;
}

Vertex rightVertex()
{
    Vertex v;
    v.x = spaceship->cx + float(spaceship->length / 2);
    v.y = spaceship->cy - float(spaceship->length / (2 * sqrt(3)));
    return v;
}

Vertex topVertex()
{
    Vertex v;
    v.x = spaceship->cx;
    v.y = spaceship->cy + float(spaceship->length / sqrt(3));
    return v;
}

void drawSpaceship()
{
    GLuint texture;
    generateTexture(&texture, "./assets/spaceship_texture.jpg");

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_TRIANGLES);

    float leftX = leftVertex().x;
    float leftY = leftVertex().y;
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(leftX, leftY);

    float rightX = rightVertex().x;
    float rightY = rightVertex().y;
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(rightX, rightY);

    float topX = topVertex().x;
    float topY = topVertex().y;
    glTexCoord2f(0.5f, 1.0f);
    glVertex2f(topX, topY);

    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void moveUp()
{
    if (topVertex().y + spaceship->speed < 300)
    {
        spaceship->cy += spaceship->speed;
    }
}

void moveDown()
{
    if (leftVertex().y - spaceship->speed > -300)
    {
        spaceship->cy -= spaceship->speed;
    }
}

void moveLeft()
{
    if (leftVertex().x - spaceship->speed > -400)
    {
        spaceship->cx -= spaceship->speed;
    }
}

void moveRight()
{
    if (rightVertex().x + spaceship->speed < 400)
    {
        spaceship->cx += spaceship->speed;
    }
}

Vertex getSpaceshipPosition()
{
    Vertex v;
    v.x = spaceship->cx;
    v.y = spaceship->cy;
    return v;
}

float collisionRadius()
{
    return float(spaceship->length / (2 * sqrt(3)));
}

int health()
{
    return spaceship->health;
}

void collide(int asteroidSize)
{
    spaceship->health -= asteroidSize / 10;
}
