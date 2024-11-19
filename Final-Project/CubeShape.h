#ifndef CUBESHAPE_H
#define CUBESHAPE_H


#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include<gl/glm/glm/glm.hpp>
#include<gl/glm/glm/ext.hpp>
#include<gl/glm/glm/gtc/matrix_transform.hpp>
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