#include <cmath>
#include <cstdlib>
#include <ctime>

#include "utils.h"

int randint(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

float euclidean_distance(Vertex v1, Vertex v2)
{
    return sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2));
}
