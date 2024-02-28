#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "utils.h"

struct Spaceship
{
    float cx;
    float cy;
    int length;
    int speed;
    int health;
};

Vertex leftVertex();
Vertex rightVertex();
Vertex topVertex();

void initSpaceship();
void drawSpaceship();
void moveUp();
void moveDown();
void moveLeft();
void moveRight();

Vertex getSpaceshipPosition();
float collisionRadius();
int health();
void collide(int asteroidSize);

#endif