#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include<gl/glm/glm/glm.hpp>
#include<gl/glm/glm/ext.hpp>
#include<gl/glm/glm/gtc/matrix_transform.hpp>
#include <vector>
#include"shape.h"

class FenceShape : public Shape {
public:
    std::vector<std::vector<GLfloat>> faces; // Stores face vertices
    std::vector<std::vector<GLfloat>> vertexColors; // Stores face colors

    GLfloat rotationAngleY;
    GLfloat rotationAngleX;
    GLfloat rotationAngleZ;
    GLfloat moving_fence_X, moving_fence_Y, moving_fence_Z;
    int num; // Used for identification
    int robot_dir; // Direction of the robot
    GLfloat size; // Size of the leg
    GLfloat width; //
    glm::vec3 position; // Position of the leg
    glm::vec3 color; // Color of the leg

    FenceShape();

    void generateFaces();
    void draw(GLuint shaderProgramID, GLuint vbo[]);

private:
    glm::mat4 createTransformMatrix();
};