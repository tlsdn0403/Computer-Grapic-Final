#ifndef SHAPE_H
#define SHAPE_H
#include <iostream>
#include <cstdlib>
#include <vector>
#include"glmFiles.hpp"

class Shape {
public:
    virtual void draw(GLuint shaderProgramID, GLuint vbo[]) = 0;
    virtual void generateFaces() = 0;
    virtual ~Shape() {}

    GLfloat position[3];
    GLfloat color[3];
    GLfloat size;
    int num;
    std::vector<std::vector<GLfloat>> faces;
    std::vector<std::vector<GLfloat>> vertexColors;
};

#endif // SHAPE_H