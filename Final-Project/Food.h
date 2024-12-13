#pragma once
#ifndef FOOD_H
#define FOOD_H


#include <iostream>
#include <vector>
#include"glmFiles.hpp"



class Food {
public:
    std::vector<std::vector<GLfloat>> faces; // Stores face vertices
    std::vector<std::vector<GLfloat>> vertexColors; // Stores face colors
    std::vector<std::vector<GLfloat>> texCoords;//�ؽ�ó�� ���� �ϴ� ����

    GLfloat rotationAngleY;
    GLfloat rotationAngleX;
    GLfloat rotationAngleZ;
    GLfloat moving_Box_X, moving_Box_Y, moving_Box_Z;
    bool valid = false;
    int num; // Used for identification
    int robot_dir; // Direction of the robot
    GLfloat size;
    GLfloat length; // �ڽ� ����
    glm::vec3 position; // Position of the leg
    glm::vec3 color; // Color of the leg

    Food();

    void generateFaces();
    virtual void draw(GLuint shaderProgramID, GLuint vbo[], GLuint textureID[]);

private:
    glm::mat4 createTransformMatrix();
};

#endif // CUBESHAPE_H