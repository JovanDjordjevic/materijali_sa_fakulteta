
#ifndef MODEL_H_
#define MODEL_H_

#include <GL/gl.h>

class Model {
public:
    Model(const char * filename, int mode);

    void draw() const;

private:
    GLfloat * vertices;
    GLfloat * colors;
    GLint   * polygons;

    int verticesNumber;
    int polygonsNumber;
    int polygonMode;

};

#endif // MODEL_H_
