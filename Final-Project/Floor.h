#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include<glm/glm/glm.hpp>
#include<glm/glm/ext.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
#include <vector>



class Floor {
public:
    std::vector<std::vector<GLfloat>> faces; // Stores face vertices
    std::vector<std::vector<GLfloat>> vertexColors; // Stores face colors
    std::vector<std::vector<GLfloat>> texCoords;//텍스처를 저장 하는 벡터

    GLfloat rotationAngleY;
    GLfloat rotationAngleX;
    GLfloat rotationAngleZ;
    GLfloat moving_Box_X, moving_Box_Y, moving_Box_Z;
    int num; // Used for identification
    int robot_dir; // Direction of the robot
    GLfloat size;
    GLfloat length; // 바닥 길이
    glm::vec3 position; // Position of the leg
    glm::vec3 color; // Color of the leg

    Floor();

    void generateFaces();
    virtual void draw(GLuint shaderProgramID, GLuint vbo[], GLuint textureID[]);

private:
    glm::mat4 createTransformMatrix();
};
