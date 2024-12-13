#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include<glm/glm.hpp>
#include<glm/ext.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include <vector>
#include"FenceShape.h"

class longFence : public FenceShape {
public:
    std::vector<std::vector<GLfloat>> faces; // Stores face vertices
    std::vector<std::vector<GLfloat>> vertexColors; // Stores face colors
    std::vector<std::vector<GLfloat>> texCoords;//�ؽ�ó�� ���� �ϴ� ����

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

    longFence();

    void generateFaces();
    virtual void draw(GLuint shaderProgramID, GLuint vbo[], GLuint textureID[]);

private:
    glm::mat4 createTransformMatrix();
};