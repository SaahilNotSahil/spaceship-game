#ifndef UTILS_H
#define UTILS_H

struct Vertex
{
    float x;
    float y;
};

int randint(int min, int max);
float euclidean_distance(Vertex v1, Vertex v2);
void Write(char *string);
void generateTexture(GLuint *texture, const char *filename);

#endif