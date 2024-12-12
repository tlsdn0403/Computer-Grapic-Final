#ifndef CUBESHAPE_H
#define CUBESHAPE_H

#include <vector>
#include"shape.h"


class CubeShape : public Shape {
public:
    CubeShape();
    void generateFaces() override;
    void draw(GLuint shaderProgramID, GLuint vbo[]) override;

    GLfloat frontRotatingAngel;
    GLfloat frontFaceAngel = 90.0f; 
};

#endif // CUBESHAPE_H