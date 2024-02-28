#define STB_IMAGE_IMPLEMENTATION

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <GL/freeglut.h>
#include <GLES2/gl2.h>
#include <iostream>

#include "stb_image.h"
#include "utils.h"

int randint(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

float euclidean_distance(Vertex v1, Vertex v2)
{
    return sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2));
}

void Write(char *string)
{
    while (*string)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string++);
    }
}

void generateTexture(GLuint *texture, const char *filename)
{
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}
