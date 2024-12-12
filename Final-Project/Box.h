#pragma once
#ifndef BOX_H
#define BOX_H


#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include<gl/glm/glm/glm.hpp>
#include<gl/glm/glm/ext.hpp>
#include<gl/glm/glm/gtc/matrix_transform.hpp>
#include <vector>



class Box  {
public:
    std::vector<std::vector<GLfloat>> faces; // Stores face vertices
    std::vector<std::vector<GLfloat>> vertexColors; // Stores face colors
    std::vector<std::vector<GLfloat>> texCoords;//�ؽ�ó�� ���� �ϴ� ����

    GLfloat rotationAngleY;
    GLfloat rotationAngleX;
    GLfloat rotationAngleZ;
    GLfloat moving_Box_X, moving_Box_Y, moving_Box_Z;
    int num; // Used for identification
    int robot_dir; // Direction of the robot
    GLfloat size; // Size of the leg
    GLfloat length; // �ڽ� ����
    glm::vec3 position; // Position of the leg
    glm::vec3 color; // Color of the leg

    Box();

    void generateFaces();
    virtual void draw(GLuint shaderProgramID, GLuint vbo[], GLuint textureID[]);

private:
    glm::mat4 createTransformMatrix();
};

#endif // CUBESHAPE_H