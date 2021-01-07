
#include "Model.h"

#include <cstdio>
#include <cstdlib>

Model::Model(const char * filename, int mode)
    : polygonMode(mode)
{

    FILE * file = fopen(filename, "r");

    fscanf(file, "%d %d", &verticesNumber, &polygonsNumber);

    vertices = (GLfloat *) malloc(verticesNumber * sizeof(GLfloat) * 3);
    colors   = (GLfloat *) malloc(verticesNumber * sizeof(GLfloat) * 4);
    polygons = (GLint *)   malloc(polygonsNumber * sizeof(GLint) * 3);

    for (int i = 0; i < verticesNumber * 3; i++) {
        fscanf(file, "%f", vertices + i);
    }

    for (int i = 0; i < verticesNumber * 4; i++) {
        fscanf(file, "%f", colors + i);
    }

    for (int i = 0; i < polygonsNumber * 3; i++) {
        fscanf(file, "%d", polygons + i);
    }

    fclose(file);
}

void Model::draw() const
{
    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

    glBegin(GL_TRIANGLES);

    for (int i = 0; i < polygonsNumber; i++) {
        for (int j = 0; j < 3; j++) {
            glColor4fv(colors + 4 * polygons[3 * i + j]);
            glVertex3fv(vertices + 3 * polygons[3 * i + j]);
        }
    }

    glEnd();

    // reset na FILL
    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

}
