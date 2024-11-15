#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include<gl/glm/glm/glm.hpp>
#include<gl/glm/glm/ext.hpp>
#include<gl/glm/glm/gtc/matrix_transform.hpp>
#include <cstdlib>
#include <random>
#include <fstream>
#include <vector>

bool projection, rotate_mid, rotateBarrel, rotateArm , frontFaceOpen,isWalking,isJumping = false;
bool isDepthTest = false;
GLfloat rotationAngleX, frontFaceAngel = 0;
GLfloat rotationBarrelAngle, rotationArmAngle = 0;
GLfloat rotateMiddle = 0;
GLfloat movingX = 0;
GLfloat movingY = 0;
GLfloat movingZ = 0;
GLfloat moving_barrel = 0;
GLfloat rotationAngleY = 0;
GLfloat rotationAngleZ = 0;
GLfloat cameraZ = 0;
GLfloat cameraX = 0;
GLfloat speed = 0.01f;
int robot_dir = 0;
void drawScene();

void make_cube(GLfloat x, GLfloat y, GLfloat z);
void make_line();
void frontOpen(int value);
void walking(int value);
void jumping(int value);
void Reshape(int w, int h);
void InitBuffer();
void drawObjects();
void make_shaderProgram();
void make_vertexShaders();
void make_fragmentShaders();
void Keyboard(unsigned char key, int x, int y);
void Cleanup();
void getOpenGLMouseCoords(int mouseX, int mouseY, float& openglX, float& openglY) {
    openglX = (static_cast<float>(mouseX) / glutGet(GLUT_WINDOW_WIDTH)) * 2.0f - 1.0f; //X
    openglY = -((static_cast<float>(mouseY) / glutGet(GLUT_WINDOW_HEIGHT)) * 2.0f - 1.0f); // Y
}


char* filetobuf(const char* file) {
    FILE* fptr;
    long length;
    char* buf;
    fptr = fopen(file, "rb");
    if (!fptr)
        return NULL;
    fseek(fptr, 0, SEEK_END);
    length = ftell(fptr);
    buf = (char*)malloc(length + 1);
    fseek(fptr, 0, SEEK_SET);
    fread(buf, length, 1, fptr);
    fclose(fptr);
    buf[length] = 0;
    return buf;
}
class Shape {
public:
    virtual void draw(GLuint shaderProgramID, GLuint vbo[]) = 0;
    virtual void generateFaces() = 0;
    void applyTopFaceTransformation(glm::mat4 Tx, int index) {

    }
    virtual ~Shape() {}
    GLfloat position[6];
    GLfloat color[3];
    GLfloat size;
    int num;
    std::vector<std::vector<GLfloat>> faces; // 6개의 면을 저장
    std::vector<std::vector<GLfloat>> vertexColors;//색을 저장 하는 벡터

};

class CubeShape : public Shape {
public:
    std::vector<std::vector<GLfloat>> faces; // 면을 저장 
    std::vector<std::vector<GLfloat>> vertexColors;//색을 저장 하는 벡터
    GLfloat frontRotatingAngel = 0.0f;
    CubeShape() {
        faces.resize(6); // 6개의 면을 위한 공간 할당
        vertexColors.resize(6);
    }
    void generateFaces() {

        // 각 면의 정점 데이터를 초기화
        // Front Face (Z+)
        faces[0] = {  // 바닥
        position[0] - size, position[1] -size , position[2] + size,  // v1 (Top-left)
        position[0] + size, position[1] - size , position[2] + size,  // v2 (Top-right)
        position[0] - size, position[1] - size , position[2] - size,  // v3 (Bottom-left)
        position[0] + size, position[1] - size , position[2] - size   // v4 (Bottom-right)
        };

        vertexColors[0] = {
            1.0f, 1.0f, 1.0f,  // v1 (Red)
           1.0f, 1.0f, 1.0f,  // v2 (Green)
            1.0f, 1.0f, 1.0f,  // v3 (Blue)
           1.0f, 1.0f, 1.0f  // v4 (Yellow)
        };
        faces[1] = {  // 오 옆면
        position[0] + size, position[1] - size , position[2] + size,  // v1 (Top-left)
        position[0] + size, position[1] - size, position[2] - size,  // v2 (Top-right)
        position[0] + size, position[1] + size , position[2] + size,  // v3 (Bottom-left)
        position[0] + size, position[1] + size , position[2] - size   // v4 (Bottom-right)
        };

        // Corresponding color data for each vertex (adjust as needed)
        vertexColors[1] = {
            1.0f, 1.0f, 0.0f,  // v1 (Red)
            1.0f, 1.0f, 0.0f,  // v2 (Green)
            1.0f, 1.0f, 0.0f,  // v3 (Blue)
            1.0f, 1.0f, 0.0f   // v4 (Yellow)
        };
        faces[2] = {  // 앞면
        position[0] - size, position[1] - size , position[2] + size,  // v1 (Top-left)
        position[0] + size, position[1] - size, position[2] + size,  // v2 (Top-right)
        position[0] - size, position[1] + size , position[2] + size,  // v3 (Bottom-left)
        position[0] + size, position[1] + size , position[2] + size   // v4 (Bottom-right)
        };

        // Corresponding color data for each vertex (adjust as needed)
        vertexColors[2] = {
            1.0f, 0.0f, 1.0f,  // v1 (Red)
            1.0f, 0.0f, 1.0f,  // v2 (Green)
            1.0f, 0.0f, 1.0f,  // v3 (Blue)
            1.0f, 0.0f, 1.0f   // v4 (Yellow)
        };
        faces[3] = {  // 오 옆면
        position[0] - size, position[1] - size, position[2] + size,  // v1 (Top-left)
        position[0] - size, position[1] - size, position[2] - size,  // v2 (Top-right)
        position[0] - size, position[1] + size , position[2] + size,  // v3 (Bottom-left)
        position[0] - size, position[1] + size , position[2] - size   // v4 (Bottom-right)
        };

        // Corresponding color data for each vertex (adjust as needed)
        vertexColors[3] = {
            0.0f, 1.0f, 1.0f,  // v1 (Red)
            0.0f, 1.0f, 1.0f,  // v2 (Green)
            0.0f, 1.0f, 1.0f,  // v3 (Blue)
            0.0f, 1.0f, 1.0f   // v4 (Yellow)
        };
        faces[4] = {  // 뒷면
        position[0] - size, position[1] - size, position[2] - size,  // v1 (Top-left)
        position[0] + size, position[1] - size, position[2] - size,  // v2 (Top-right)
        position[0] - size, position[1] + size , position[2] - size,  // v3 (Bottom-left)
        position[0] + size, position[1] + size , position[2] - size   // v4 (Bottom-right)
        };

        // Corresponding color data for each vertex (adjust as needed)
        vertexColors[4] = {
            1.0f, 0.0f, 0.0f,  // v1 (Red)
            1.0f, 0.0f, 0.0f,  // v2 (Green)
            1.0f, 0.0f, 0.0f,  // v3 (Blue)
            1.0f, 0.0f, 0.0f   // v4 (Yellow)
        };
        faces[5] = {  // 윗면
        position[0] - size, position[1] + size, position[2] + size,  // v1 (Top-left)
        position[0] + size, position[1] + size , position[2] + size,  // v2 (Top-right)
        position[0] - size, position[1] + size , position[2] - size,  // v3 (Bottom-left)
        position[0] + size, position[1] + size, position[2] - size   // v4 (Bottom-right)
        };

        vertexColors[5] = {
            0.0f, 1.0f, 0.0f,  // v1 (Red)
            0.0f, 1.0f, 0.0f,  // v2 (Green)
            0.0f, 1.0f, 0.0f,  // v3 (Blue)
            0.0f, 1.0f, 0.0f   // v4 (Yellow)
        };


    }
    void draw(GLuint shaderProgramID, GLuint vbo[]) {
        for (int i = 0; i < 6; i++) {
            if (i >= faces.size()) {
                std::cerr << "Error: faces vector index out of range." << std::endl;
                continue;
            }
            glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
            glBufferSubData(GL_ARRAY_BUFFER, 0, faces[i].size() * sizeof(GLfloat), faces[i].data());
            glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); // vbo[1]에 색상 정보 저장
            glBufferSubData(GL_ARRAY_BUFFER, 0, vertexColors[i].size() * sizeof(GLfloat), vertexColors[i].data());

            

            glm::mat4 Tx = glm::mat4(1.0f);
            Tx = glm::translate(Tx, glm::vec3(0.0 , 0.0, 0.0)); // 이동행렬



            glm::mat4 Rz = glm::mat4(1.0f);
            Rz = glm::rotate(Rz, glm::radians(10.0f), glm::vec3(1.00, 0.00, 0.0)); //기본적인 회전 행렬

            glm::mat4 Ry = glm::mat4(1.0f);
            Ry = glm::rotate(Ry, glm::radians(rotateMiddle), glm::vec3(0.00, 1.00, 0.0)); //기본적인 회전 행렬


            glm::mat4 TR = glm::mat4(1.0f);
            TR = Tx * Rz;
            glm::mat4 modelMatrix = Tx;
            if (i == 2 && (frontFaceOpen == true )) {  // Apply front face opening rotation
                frontRotatingAngel = frontFaceAngel;
                glm::mat4 translateToEdge = glm::translate(glm::mat4(1.0f), glm::vec3(0,-size , size));
                glm::mat4 translateBack = glm::translate(glm::mat4(1.0f), glm::vec3(0, +size, -size));

                glm::mat4 Rz_FRONT = glm::rotate(glm::mat4(1.0f), glm::radians(frontRotatingAngel), glm::vec3(1.0f, 0.0f, 0.0f));

                modelMatrix = Tx * translateToEdge * Rz_FRONT * translateBack;
            }
            GLuint mvpLocation = glGetUniformLocation(shaderProgramID, "uMVP");
            
            glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); // Draw the face using four vertice
        }
    }
};
class RobotLeg: public Shape {
public:
    std::vector<std::vector<GLfloat>> faces; // 면을 저장 
    std::vector<std::vector<GLfloat>> vertexColors;//색을 저장 하는 벡터
    GLfloat rotateY = rotationAngleY;
    RobotLeg() {
        faces.resize(6); // 6개의 면을 위한 공간 할당
        vertexColors.resize(6);
    }
    void generateFaces() {
        float heightMultiplier = 20.0f; // Make the cube longer along the y-axis

        // Front Face (Z+)
        faces[0] = {
            position[0] - size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-left
            position[0] + size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-right
            position[0] - size, position[1], position[2] + size,  // Top-left
            position[0] + size, position[1] , position[2] + size   // Top-right
        };
        vertexColors[0] = {
             color[0], color[1], color[2],  // Blue
            color[0], color[1], color[2],
            color[0], color[1], color[2],
            color[0], color[1], color[2]
        };

        // Right Face (X+)
        faces[1] = {
            position[0] + size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-left
            position[0] + size, position[1] - size * heightMultiplier, position[2] - size,  // Bottom-right
            position[0] + size, position[1] , position[2] + size,  // Top-left
            position[0] + size, position[1] , position[2] - size   // Top-right
        };
        vertexColors[1] = {
             color[0], color[1], color[2],  // Blue
            color[0], color[1], color[2],
            color[0], color[1], color[2],
            color[0], color[1], color[2]
        };

        // Back Face (Z-)
        faces[2] = {
            position[0] - size, position[1] - size * heightMultiplier, position[2] - size,  // Bottom-left
            position[0] + size, position[1] - size * heightMultiplier, position[2] - size,  // Bottom-right
            position[0] - size, position[1] , position[2] - size,  // Top-left
            position[0] + size, position[1] , position[2] - size   // Top-right
        };
        vertexColors[2] = {
            color[0], color[1], color[2],  // Blue
            color[0], color[1], color[2],
            color[0], color[1], color[2],
            color[0], color[1], color[2]
        };

        // Left Face (X-)
        faces[3] = {
            position[0] - size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-left
            position[0] - size, position[1] - size * heightMultiplier, position[2] - size,  // Bottom-right
            position[0] - size, position[1] , position[2] + size,  // Top-left
            position[0] - size, position[1] , position[2] - size   // Top-right
        };
        vertexColors[3] = {
             color[0], color[1], color[2],  // Blue
            color[0], color[1], color[2],
            color[0], color[1], color[2],
            color[0], color[1], color[2]
        };

        // Top Face (Y+)
        faces[4] = {
            position[0] - size, position[1] , position[2] + size,  // Bottom-left
            position[0] + size, position[1] , position[2] + size,  // Bottom-right
            position[0] - size, position[1] , position[2] - size,  // Top-left
            position[0] + size, position[1] , position[2] - size   // Top-right
        };
        vertexColors[4] = {
             color[0], color[1], color[2],  // Blue
            color[0], color[1], color[2],
            color[0], color[1], color[2],
            color[0], color[1], color[2]
        };

        // Bottom Face (Y-)
        faces[5] = {
            position[0] - size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-left
            position[0] + size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-right
            position[0] - size, position[1] - size * heightMultiplier, position[2] - size,  // Top-left
            position[0] + size, position[1] - size * heightMultiplier, position[2] - size   // Top-right
        };
        vertexColors[5] = {
             color[0], color[1], color[2],  // Blue
            color[0], color[1], color[2],
            color[0], color[1], color[2],
            color[0], color[1], color[2]
        };
    }
    //팔은 num=2,3임
    void draw(GLuint shaderProgramID, GLuint vbo[]) {
        for (int i = 0; i < 6; i++) {
            if (i >= faces.size()) {
                std::cerr << "Error: faces vector index out of range." << std::endl;
                continue;
            }
            glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
            glBufferSubData(GL_ARRAY_BUFFER, 0, faces[i].size() * sizeof(GLfloat), faces[i].data());
            glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); // vbo[1]에 색상 정보 저장         
            glBufferSubData(GL_ARRAY_BUFFER, 0, vertexColors[i].size() * sizeof(GLfloat), vertexColors[i].data());



            glm::mat4 Tx = glm::mat4(1.0f);
            Tx = glm::translate(Tx, glm::vec3(0.0 + movingX, 0.0+ movingY, 0.0 + movingZ)); // 이동행렬
            
            glm::mat4 Ty_1 = glm::mat4(1.0f);
            glm::mat4 Ty_2 = glm::mat4(1.0f);
            if (num == 0 || num == 1) {
                Ty_1 = glm::translate(Ty_1, glm::vec3(0.0, 0.6, 0.0)); // 이동행렬
                Ty_2 = glm::translate(Ty_2, glm::vec3(0.0, -0.6, 0.0)); // 이동행렬
            }
            else {
                Ty_1 = glm::translate(Ty_1, glm::vec3(0.0, 0.2, 0.0)); // 이동행렬
                Ty_2 = glm::translate(Ty_2, glm::vec3(0.0, -0.2, 0.0)); // 이동행렬
            }
            
            glm::mat4 Ry = glm::mat4(1.0f);
            Ry = glm::rotate(Ry, glm::radians(rotationAngleY), glm::vec3(0.00, 1.00, 0.0));

            glm::mat4 Rx = glm::mat4(1.0f);
            

            glm::mat4 Rz = glm::mat4(1.0f);
            if (num == 1||num==2) {
                Rz = glm::rotate(Rz, glm::radians(rotationAngleZ), glm::vec3(0.00, 0.00, 1.0));
                Rx = glm::rotate(Rx, glm::radians(+rotationAngleX), glm::vec3(1.00, 0.00, 0.0));

            }
            else {
                Rz = glm::rotate(Rz, glm::radians(-rotationAngleZ), glm::vec3(0.00, 0.00, 1.0));
                Rx = glm::rotate(Rx, glm::radians(-rotationAngleX), glm::vec3(1.00, 0.00, 0.0));
            }


            glm::mat4 TR = glm::mat4(1.0f);
            if (robot_dir == 4 || robot_dir == 6) {
                TR = Tx * Ty_2 * Rz * Ry * Ty_1;
            }
            else {
                TR = Tx * Ty_2 * Rx * Ry * Ty_1;
            }

            GLuint mvpLocation = glGetUniformLocation(shaderProgramID, "uMVP");
            glm::mat4 modelMatrix = TR;
            glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));

            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); // Draw the face using four vertices      
        }
    }


};
class RobotBody : public Shape {
public:
    std::vector<std::vector<GLfloat>> faces; // 면을 저장 
    std::vector<std::vector<GLfloat>> vertexColors;//색을 저장 하는 벡터
    GLfloat rotateY = rotationAngleY;
    RobotBody() {
        faces.resize(6); // 6개의 면을 위한 공간 할당
        vertexColors.resize(6);
    }
    void generateFaces() {
        float heightMultiplier = 2.0f; // Make the cube longer along the y-axis

        // Front Face (Z+)
        faces[0] = {
            position[0] - size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-left
            position[0] + size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-right
            position[0] - size, position[1] + size * heightMultiplier, position[2] + size,  // Top-left
            position[0] + size, position[1] + size * heightMultiplier, position[2] + size   // Top-right
        };
        vertexColors[0] = {
             color[0], color[1], color[2],  // Blue
            color[0], color[1], color[2],
            color[0], color[1], color[2],
            color[0], color[1], color[2]
        };

        // Right Face (X+)
        faces[1] = {
            position[0] + size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-left
            position[0] + size, position[1] - size * heightMultiplier, position[2] - size,  // Bottom-right
            position[0] + size, position[1] + size * heightMultiplier, position[2] + size,  // Top-left
            position[0] + size, position[1] + size * heightMultiplier, position[2] - size   // Top-right
        };
        vertexColors[1] = {
             color[0], color[1], color[2],  // Blue
            color[0], color[1], color[2],
            color[0], color[1], color[2],
            color[0], color[1], color[2]
        };

        // Back Face (Z-)
        faces[2] = {
            position[0] - size, position[1] - size * heightMultiplier, position[2] - size,  // Bottom-left
            position[0] + size, position[1] - size * heightMultiplier, position[2] - size,  // Bottom-right
            position[0] - size, position[1] + size * heightMultiplier, position[2] - size,  // Top-left
            position[0] + size, position[1] + size * heightMultiplier, position[2] - size   // Top-right
        };
        vertexColors[2] = {
            color[0], color[1], color[2],  // Blue
            color[0], color[1], color[2],
            color[0], color[1], color[2],
            color[0], color[1], color[2]
        };

        // Left Face (X-)
        faces[3] = {
            position[0] - size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-left
            position[0] - size, position[1] - size * heightMultiplier, position[2] - size,  // Bottom-right
            position[0] - size, position[1] + size * heightMultiplier, position[2] + size,  // Top-left
            position[0] - size, position[1] + size * heightMultiplier, position[2] - size   // Top-right
        };
        vertexColors[3] = {
             color[0], color[1], color[2],  // Blue
            color[0], color[1], color[2],
            color[0], color[1], color[2],
            color[0], color[1], color[2]
        };

        // Top Face (Y+)
        faces[4] = {
            position[0] - size, position[1] + size * heightMultiplier, position[2] + size,  // Bottom-left
            position[0] + size, position[1] + size * heightMultiplier, position[2] + size,  // Bottom-right
            position[0] - size, position[1] + size * heightMultiplier, position[2] - size,  // Top-left
            position[0] + size, position[1] + size * heightMultiplier, position[2] - size   // Top-right
        };
        vertexColors[4] = {
             color[0], color[1], color[2],  // Blue
            color[0], color[1], color[2],
            color[0], color[1], color[2],
            color[0], color[1], color[2]
        };

        // Bottom Face (Y-)
        faces[5] = {
            position[0] - size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-left
            position[0] + size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-right
            position[0] - size, position[1] - size * heightMultiplier, position[2] - size,  // Top-left
            position[0] + size, position[1] - size * heightMultiplier, position[2] - size   // Top-right
        };
        vertexColors[5] = {
             color[0], color[1], color[2],  // Blue
            color[0], color[1], color[2],
            color[0], color[1], color[2],
            color[0], color[1], color[2]
        };
    }

    void draw(GLuint shaderProgramID, GLuint vbo[]) {
        for (int i = 0; i < 6; i++) {
            if (i >= faces.size()) {
                std::cerr << "Error: faces vector index out of range." << std::endl;
                continue;
            }
            glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
            glBufferSubData(GL_ARRAY_BUFFER, 0, faces[i].size() * sizeof(GLfloat), faces[i].data());
            glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); // vbo[1]에 색상 정보 저장         
            glBufferSubData(GL_ARRAY_BUFFER, 0, vertexColors[i].size() * sizeof(GLfloat), vertexColors[i].data());

        
            glm::mat4 Rx = glm::mat4(1.0f);
            glm::mat4 Tx = glm::mat4(1.0f);
            Tx = glm::translate(Tx, glm::vec3(0.0 + movingX, 0.0+movingY, 0.0 + movingZ)); // 이동행렬




            glm::mat4 Ry = glm::mat4(1.0f);
            Ry = glm::rotate(Ry, glm::radians(rotationAngleY), glm::vec3(0.00, 1.00, 0.0));




            glm::mat4 TR = glm::mat4(1.0f);
            TR =   Tx * Rx * Ry;

            GLuint mvpLocation = glGetUniformLocation(shaderProgramID, "uMVP");
            glm::mat4 modelMatrix = TR;
            glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));

            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); // Draw the face using four vertices      
        }
    }
};
class RobotFace : public Shape {
public:
    std::vector<std::vector<GLfloat>> faces; // 면을 저장 
    std::vector<std::vector<GLfloat>> vertexColors;//색을 저장 하는 벡터
    GLfloat rotateY = rotationAngleY;
    RobotFace() {
        faces.resize(6); // 6개의 면을 위한 공간 할당
        vertexColors.resize(6);
    }
    void generateFaces() {
        float heightMultiplier = 2.0f; // Make the cube longer along the y-axis

        // Front Face (Z+)
        faces[0] = {
            position[0] - size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-left
            position[0] + size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-right
            position[0] - size, position[1] + size * heightMultiplier, position[2] + size,  // Top-left
            position[0] + size, position[1] + size * heightMultiplier, position[2] + size   // Top-right
        };
        vertexColors[0] = {
             1, 1, 0,  // Blue
            1, 1, 0,
            1, 1, 0,
            1,1, 0
        };

        // Right Face (X+)
        faces[1] = {
            position[0] + size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-left
            position[0] + size, position[1] - size * heightMultiplier, position[2] - size,  // Bottom-right
            position[0] + size, position[1] + size * heightMultiplier, position[2] + size,  // Top-left
            position[0] + size, position[1] + size * heightMultiplier, position[2] - size   // Top-right
        };
        vertexColors[1] = {
             color[0], color[1], color[2],  // Blue
            color[0], color[1], color[2],
            color[0], color[1], color[2],
            color[0], color[1], color[2]
        };

        // Back Face (Z-)
        faces[2] = {
            position[0] - size, position[1] - size * heightMultiplier, position[2] - size,  // Bottom-left
            position[0] + size, position[1] - size * heightMultiplier, position[2] - size,  // Bottom-right
            position[0] - size, position[1] + size * heightMultiplier, position[2] - size,  // Top-left
            position[0] + size, position[1] + size * heightMultiplier, position[2] - size   // Top-right
        };
        vertexColors[2] = {
            color[0], color[1], color[2],  // Blue
            color[0], color[1], color[2],
            color[0], color[1], color[2],
            color[0], color[1], color[2]
        };

        // Left Face (X-)
        faces[3] = {
            position[0] - size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-left
            position[0] - size, position[1] - size * heightMultiplier, position[2] - size,  // Bottom-right
            position[0] - size, position[1] + size * heightMultiplier, position[2] + size,  // Top-left
            position[0] - size, position[1] + size * heightMultiplier, position[2] - size   // Top-right
        };
        vertexColors[3] = {
             color[0], color[1], color[2],  // Blue
            color[0], color[1], color[2],
            color[0], color[1], color[2],
            color[0], color[1], color[2]
        };

        // Top Face (Y+)
        faces[4] = {
            position[0] - size, position[1] + size * heightMultiplier, position[2] + size,  // Bottom-left
            position[0] + size, position[1] + size * heightMultiplier, position[2] + size,  // Bottom-right
            position[0] - size, position[1] + size * heightMultiplier, position[2] - size,  // Top-left
            position[0] + size, position[1] + size * heightMultiplier, position[2] - size   // Top-right
        };
        vertexColors[4] = {
             color[0], color[1], color[2],  // Blue
            color[0], color[1], color[2],
            color[0], color[1], color[2],
            color[0], color[1], color[2]
        };

        // Bottom Face (Y-)
        faces[5] = {
            position[0] - size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-left
            position[0] + size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-right
            position[0] - size, position[1] - size * heightMultiplier, position[2] - size,  // Top-left
            position[0] + size, position[1] - size * heightMultiplier, position[2] - size   // Top-right
        };
        vertexColors[5] = {
             color[0], color[1], color[2],  // Blue
            color[0], color[1], color[2],
            color[0], color[1], color[2],
            color[0], color[1], color[2]
        };
    }

    void draw(GLuint shaderProgramID, GLuint vbo[]) {
        for (int i = 0; i < 6; i++) {
            if (i >= faces.size()) {
                std::cerr << "Error: faces vector index out of range." << std::endl;
                continue;
            }
            glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
            glBufferSubData(GL_ARRAY_BUFFER, 0, faces[i].size() * sizeof(GLfloat), faces[i].data());
            glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); // vbo[1]에 색상 정보 저장         
            glBufferSubData(GL_ARRAY_BUFFER, 0, vertexColors[i].size() * sizeof(GLfloat), vertexColors[i].data());


            glm::mat4 Rx = glm::mat4(1.0f);
            glm::mat4 Tx = glm::mat4(1.0f);
            Tx = glm::translate(Tx, glm::vec3(0.0 + movingX, 0.0+ movingY, 0.0 + movingZ)); // 이동행렬




            glm::mat4 Ry = glm::mat4(1.0f);
            Ry = glm::rotate(Ry, glm::radians(rotationAngleY), glm::vec3(0.00, 1.00, 0.0));




            glm::mat4 TR = glm::mat4(1.0f);
            TR = Tx * Rx * Ry;

            GLuint mvpLocation = glGetUniformLocation(shaderProgramID, "uMVP");
            glm::mat4 modelMatrix = TR;
            glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));

            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); // Draw the face using four vertices      
        }
    }
};
class ObstacleShape : public Shape {
public:
    std::vector<std::vector<GLfloat>> faces; // 면을 저장 
    std::vector<std::vector<GLfloat>> vertexColors;//색을 저장 하는 벡터
    GLfloat frontRotatingAngel = 0.0f;
    ObstacleShape() {
        faces.resize(6); // 6개의 면을 위한 공간 할당
        vertexColors.resize(6);
    }
    void generateFaces() {

        // 각 면의 정점 데이터를 초기화
        // Front Face (Z+)
        faces[0] = {  // 바닥
        position[0] - size, position[1] - size , position[2] + size,  // v1 (Top-left)
        position[0] + size, position[1] - size , position[2] + size,  // v2 (Top-right)
        position[0] - size, position[1] - size , position[2] - size,  // v3 (Bottom-left)
        position[0] + size, position[1] - size , position[2] - size   // v4 (Bottom-right)
        };

        vertexColors[0] = {
            0.0f, 0.0f, 0.0f,  // v1 (Red)
           0.0f, 0.0f, 0.0f,  // v2 (Green)
            0.0f, 0.0f, 0.0f,  // v3 (Blue)
           0.0f, 0.0f, 0.0f  // v4 (Yellow)
        };
        faces[1] = {  // 오 옆면
        position[0] + size, position[1] - size , position[2] + size,  // v1 (Top-left)
        position[0] + size, position[1] - size, position[2] - size,  // v2 (Top-right)
        position[0] + size, position[1] + size , position[2] + size,  // v3 (Bottom-left)
        position[0] + size, position[1] + size , position[2] - size   // v4 (Bottom-right)
        };

        // Corresponding color data for each vertex (adjust as needed)
        vertexColors[1] = {
             0.0f, 0.0f, 0.0f,  // v1 (Red)
           0.0f, 0.0f, 0.0f,  // v2 (Green)
            0.0f, 0.0f, 0.0f,  // v3 (Blue)
           0.0f, 0.0f, 0.0f  // v4 (Yellow)
        };
        faces[2] = {  // 앞면
        position[0] - size, position[1] - size , position[2] + size,  // v1 (Top-left)
        position[0] + size, position[1] - size, position[2] + size,  // v2 (Top-right)
        position[0] - size, position[1] + size , position[2] + size,  // v3 (Bottom-left)
        position[0] + size, position[1] + size , position[2] + size   // v4 (Bottom-right)
        };

        // Corresponding color data for each vertex (adjust as needed)
        vertexColors[2] = {
             0.0f, 0.0f, 0.0f,  // v1 (Red)
           0.0f, 0.0f, 0.0f,  // v2 (Green)
            0.0f, 0.0f, 0.0f,  // v3 (Blue)
           0.0f, 0.0f, 0.0f  // v4 (Yellow)
        };
        faces[3] = {  // 오 옆면
        position[0] - size, position[1] - size, position[2] + size,  // v1 (Top-left)
        position[0] - size, position[1] - size, position[2] - size,  // v2 (Top-right)
        position[0] - size, position[1] + size , position[2] + size,  // v3 (Bottom-left)
        position[0] - size, position[1] + size , position[2] - size   // v4 (Bottom-right)
        };

        // Corresponding color data for each vertex (adjust as needed)
        vertexColors[3] = {
             0.0f, 0.0f, 0.0f,  // v1 (Red)
           0.0f, 0.0f, 0.0f,  // v2 (Green)
            0.0f, 0.0f, 0.0f,  // v3 (Blue)
           0.0f, 0.0f, 0.0f  // v4 (Yellow)
        };
        faces[4] = {  // 뒷면
        position[0] - size, position[1] - size, position[2] - size,  // v1 (Top-left)
        position[0] + size, position[1] - size, position[2] - size,  // v2 (Top-right)
        position[0] - size, position[1] + size , position[2] - size,  // v3 (Bottom-left)
        position[0] + size, position[1] + size , position[2] - size   // v4 (Bottom-right)
        };

        // Corresponding color data for each vertex (adjust as needed)
        vertexColors[4] = {
             0.0f, 0.0f, 0.0f,  // v1 (Red)
           0.0f, 0.0f, 0.0f,  // v2 (Green)
            0.0f, 0.0f, 0.0f,  // v3 (Blue)
           0.0f, 0.0f, 0.0f  // v4 (Yellow)
        };
        faces[5] = {  // 윗면
        position[0] - size, position[1] + size, position[2] + size,  // v1 (Top-left)
        position[0] + size, position[1] + size , position[2] + size,  // v2 (Top-right)
        position[0] - size, position[1] + size , position[2] - size,  // v3 (Bottom-left)
        position[0] + size, position[1] + size, position[2] - size   // v4 (Bottom-right)
        };

        vertexColors[5] = {
             0.0f, 0.0f, 0.0f,  // v1 (Red)
           0.0f, 0.0f, 0.0f,  // v2 (Green)
            0.0f, 0.0f, 0.0f,  // v3 (Blue)
           0.0f, 0.0f, 0.0f  // v4 (Yellow)
        };


    }
    void draw(GLuint shaderProgramID, GLuint vbo[]) {
        for (int i = 0; i < 6; i++) {
            if (i >= faces.size()) {
                std::cerr << "Error: faces vector index out of range." << std::endl;
                continue;
            }
            glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
            glBufferSubData(GL_ARRAY_BUFFER, 0, faces[i].size() * sizeof(GLfloat), faces[i].data());
            glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); // vbo[1]에 색상 정보 저장
            glBufferSubData(GL_ARRAY_BUFFER, 0, vertexColors[i].size() * sizeof(GLfloat), vertexColors[i].data());



            glm::mat4 Tx = glm::mat4(1.0f);
            Tx = glm::translate(Tx, glm::vec3(0.0, 0.0, 0.0)); // 이동행렬
            GLuint mvpLocation = glGetUniformLocation(shaderProgramID, "uMVP");

            glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(Tx));
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); // Draw the face using four vertice
        }
    }
};


struct obstacle {
    GLfloat posittion[3];
};
obstacle ob_1;
obstacle ob_2;
obstacle ob_3;
GLchar* vertexSource, * fragmentSource;
GLuint vertexShader, fragmentShader;
GLuint shaderProgramID;
GLuint vao, vboArr[2];
std::vector<Shape*> shapes;
std::vector<Shape*> shapes_line;

bool drawWireframe = false;
bool isRotatingX = false;


bool isOpenging = false;

GLfloat translateX = 0;
GLfloat translateY = 0;
const int MAX_SHAPES = 10;
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);

int windowWidth = 800;
int windowHeight = 600;
GLfloat aspect = windowWidth / windowHeight; //종횡비


// Main function
int main(int argc, char** argv) {
    //--- Create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL Shapes Example");
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //--- GLEW 초기화하기
    glewExperimental = GL_TRUE;
    GLenum glewStatus = glewInit();
    if (glewStatus != GLEW_OK) {
        std::cerr << "GLEW Initialization failed: " << glewGetErrorString(glewStatus) << std::endl;
        return EXIT_FAILURE;
    }

    make_shaderProgram();
    InitBuffer();
    //--- Register callback functions

    drawObjects();

    glutDisplayFunc(drawScene);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);
    glutPostRedisplay(); // 화면 다시 그리기
    atexit(Cleanup); //메모리 누수 방지 (new로 할당된 객체 delete)

    glutMainLoop();
    return 0;
}


void drawScene() {
    glClearColor(0.0, 0.0, 0.0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST); // Ensure depth testing is enabled

    glUseProgram(shaderProgramID);
    glBindVertexArray(vao);

    glViewport(0, 0, windowWidth , windowHeight);
    glm::mat4 projection;
    glm::mat4 perspectiveProjection = glm::perspective(glm::radians(90.0f), aspect, 0.1f, 10.0f);
    unsigned int projectionLocation = glGetUniformLocation(shaderProgramID, "projectionTransform");
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &perspectiveProjection[0][0]);

    glm::vec3 cameraPos = glm::vec3(0.0f + cameraX, 0.0f, 2.0f + cameraZ);
    glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f , 0.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
    unsigned int viewLocation = glGetUniformLocation(shaderProgramID, "viewTransform");
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

    for (auto shape : shapes) {
        shape->draw(shaderProgramID, vboArr);
    }

    glutSwapBuffers();
}




void Reshape(int w, int h) {

    glViewport(0, 0, w, h);
}

// 오픈지엘 버퍼 초기화
void InitBuffer() {
    glGenVertexArrays(1, &vao); //VAO 지정하고 할당
    glBindVertexArray(vao);  // VAO 바인드하기
    glGenBuffers(2, vboArr); // 2개의 VBO 할당(유니폼으로 색상을 할당함으로 1개만 필요)


    //posittion
    glBindBuffer(GL_ARRAY_BUFFER, vboArr[0]); //VBO 바인드
    glBufferData(GL_ARRAY_BUFFER, 108 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW); //최대 (6개의 정점*3개의 좌표)  (36 * 3 = 108 floats)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vboArr[1]);
    //--- 변수 colors에서 버텍스색상을복사한다.
    //--- colors 배열의 사이즈: 9 *float 
    glBufferData(GL_ARRAY_BUFFER, 108 * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
    //--- 색상값을attribute 인덱스1번에명시한다: 버텍스당3*float
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //--- attribute 인덱스 1번을 사용가능하게함.
    glEnableVertexAttribArray(1);
}

//세이더 프로그램 생성하기
void make_shaderProgram() {
    //버텍스랑 프레그먼트 세이더 만들기
    make_vertexShaders();
    make_fragmentShaders();

    // 세이더 프로그램 만들기
    shaderProgramID = glCreateProgram();

    glAttachShader(shaderProgramID, vertexShader);
    glAttachShader(shaderProgramID, fragmentShader);
    glLinkProgram(shaderProgramID);

    // 에러체크
    GLint success;
    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(shaderProgramID, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        exit(EXIT_FAILURE);
    }

    // 세이더 삭제하기
    glDeleteShader(vertexShader); //-세이더객체를 세이더프로그램에 링크했음으로,세이더객체 자체는 삭제가능
    glDeleteShader(fragmentShader);

    // Shader program 사용
    glUseProgram(shaderProgramID);
}


void make_vertexShaders() {
    vertexSource = filetobuf("vertex.glsl");
    if (!vertexSource) {
        std::cerr << "Failed to load vertex shader." << std::endl;
        exit(EXIT_FAILURE);
    }

    // 버텍스 세이더 객체 만들기
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //  세이더코드를 세이더 객체에 넣기
    glShaderSource(vertexShader, 1, (const GLchar**)&vertexSource, 0);

    glCompileShader(vertexShader);

    GLint result;
    GLchar errorLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
        std::cerr << "ERROR: vertex shader compilation failed\n" << errorLog << std::endl;
        free(vertexSource); // Free allocated memory
        exit(EXIT_FAILURE);
    }
    free(vertexSource); // Free allocated memory
}


void make_fragmentShaders() {
    //프레그먼트 파일읽기
    fragmentSource = filetobuf("fragment.glsl");
    if (!fragmentSource) {
        std::cerr << "Failed to load fragment shader." << std::endl;
        exit(EXIT_FAILURE);
    }

    // 프레그먼트 객체 만들기
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // 세이더 코드 세이더 객체에 넣기
    glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, 0);
    // 프레그먼티 세이더 컴파일
    glCompileShader(fragmentShader);
    // 컴파일 에러 체크
    GLint result;
    GLchar errorLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
        std::cerr << "ERROR: fragment shader compilation failed\n" << errorLog << std::endl;
        free(fragmentSource); // Free allocated memory
        exit(EXIT_FAILURE);
    }
    free(fragmentSource); // Free allocated memory
}


void make_cube(GLfloat x, GLfloat y, GLfloat z) {
    Shape* newShape = new CubeShape();
    newShape->position[0] = x;
    newShape->position[1] = y;
    newShape->position[2] = z;
    newShape->size = 1.0f;
    newShape->generateFaces(); // 정점 데이터 초기화
    shapes.push_back(newShape);

    Shape* newShape_2 = new ObstacleShape();
    newShape_2->position[0] = x+0.4;
    newShape_2->position[1] = y-1.0f;
    newShape_2->position[2] = z+0.4;
    newShape_2->size = 0.2f;
    newShape_2->generateFaces(); // 정점 데이터 초기화
    shapes.push_back(newShape_2);
    ob_1.posittion[0] = newShape_2->position[0];
    ob_1.posittion[1] = newShape_2->position[1];
    ob_1.posittion[2] = newShape_2->position[2];

    Shape* newShape_3 = new ObstacleShape();
    newShape_3->position[0] = x - 0.7;
    newShape_3->position[1] = y - 1.0f;
    newShape_3->position[2] = z + 0.4;
    newShape_3->size = 0.2f;
    newShape_3->generateFaces(); // 정점 데이터 초기화
    shapes.push_back(newShape_3);

    ob_2.posittion[0] = newShape_3->position[0];
    ob_2.posittion[1] = newShape_3->position[1];
    ob_2.posittion[2] = newShape_3->position[2];

    Shape* newShape_4 = new ObstacleShape();
    newShape_4->position[0] = x - 0.5;
    newShape_4->position[1] = y - 1.0f;
    newShape_4->position[2] = z - 0.5;
    newShape_4->size = 0.2f;
    newShape_4->generateFaces(); // 정점 데이터 초기화
    shapes.push_back(newShape_4);

    ob_3.posittion[0] = newShape_4->position[0];
    ob_3.posittion[1] = newShape_4->position[1];
    ob_3.posittion[2] = newShape_4->position[2];
  
    glutPostRedisplay();
}



void Keyboard(unsigned char key, int x, int y) {

    switch (key)
    {

    case'o': {
        frontFaceOpen = !frontFaceOpen;
        glutTimerFunc(60, frontOpen, 0);
        break;
    }
    case'w': {
        isWalking = !isWalking;
        robot_dir = 8;
        glutTimerFunc(12, walking, 0);
        glutPostRedisplay();
        break;
    }
    case's': {
        isWalking = !isWalking;
        robot_dir = 2;
        glutTimerFunc(12, walking, 0);
        glutPostRedisplay();
        break;
    }
    case'a': {
        isWalking = !isWalking;
        robot_dir = 4;
        glutTimerFunc(12, walking, 0);
        glutPostRedisplay();
        break;
    }
    case'd': {
        isWalking = !isWalking;
        robot_dir = 6;
        glutTimerFunc(12, walking, 0);
        glutPostRedisplay();
        break;
    }
    case 'z': {
        cameraZ += 0.1;
        glutPostRedisplay();
        break;
    }case 'Z': {
        cameraZ -= 0.1;
        if (cameraZ <= 0) {
            cameraZ = 0;
        }
        glutPostRedisplay();
        break;
    }
    case 'x': {
        cameraX += 0.1;
        glutPostRedisplay();
        break;
    }
    case 'X': {
        cameraX -= 0.1;
        
        glutPostRedisplay();
        break;
    }
    case 'c': {
        cameraX = 0;
        cameraZ = 0;
        break;
    }
    case'=':{
        speed += 0.001f;
        break;                    
    }
    case'-': {
        speed -= 0.001f;
        if (speed <= 0.005f) {
            speed = 0.005f;
        }
        break;
    }
    case'j':{
        isJumping = true;
        glutTimerFunc(12, jumping, 0);
        break;
    }
    default:
        break;
    }
    glutPostRedisplay(); // 화면 다시 그리기 요청
}


void make_clane(GLfloat x, GLfloat y, GLfloat z) {
    Shape* newShape = new RobotBody(); //아래몸체
    newShape->position[0] = x;
    newShape->position[1] = y-0.4f;
    newShape->position[2] = z;
    newShape->size = 0.1f;
    newShape->color[0] = 0;
    newShape->color[1] = 0;
    newShape->color[2] = 1;
    newShape->generateFaces(); // 정점 데이터 초기화
    shapes.push_back(newShape);

    Shape* newShape_2 = new RobotLeg(); //왼다리
    newShape_2->position[0] = x-0.05f;
    newShape_2->position[1] = y-0.6f;
    newShape_2->position[2] = z;
    newShape_2->num = 1;
    newShape_2->size = 0.02f;
    newShape_2->color[0] = 0;
    newShape_2->color[1] = 1;
    newShape_2->color[2] = 0;
    newShape_2->generateFaces(); // 정점 데이터 초기화
    shapes.push_back(newShape_2);

    Shape* newShape_3 = new RobotLeg(); //오른다리
    newShape_3->position[0] = x + 0.05f;
    newShape_3->position[1] = y - 0.6f;
    newShape_3->position[2] = z;
    newShape_3->size = 0.02f;
    newShape_3->color[0] = 1;
    newShape_3->color[1] = 1;
    newShape_3->color[2] = 0;
    newShape_3->generateFaces(); // 정점 데이터 초기화
    shapes.push_back(newShape_3);


    Shape* newShape_4 = new RobotLeg(); //왼팔
    newShape_4->position[0] = x - 0.11f;
    newShape_4->position[1] = y - 0.2f;
    newShape_4->position[2] = z;
    newShape_4->num = 2;
    newShape_4->size = 0.01f;
    newShape_4->color[0] = 1;
    newShape_4->color[1] = 0;
    newShape_4->color[2] = 1;
    newShape_4->generateFaces(); // 정점 데이터 초기화
    shapes.push_back(newShape_4);

    Shape* newShape_5 = new RobotLeg(); //오른팔
    newShape_5->position[0] = x + 0.11f;
    newShape_5->position[1] = y - 0.2f;
    newShape_5->position[2] = z;
    newShape_5->size = 0.01f;
    newShape_5->num = 3;
    newShape_5->color[0] = 0;
    newShape_5->color[1] = 1;
    newShape_5->color[2] = 1;
    newShape_5->generateFaces(); // 정점 데이터 초기화
    shapes.push_back(newShape_5);

    Shape* newShape_6 = new RobotFace(); //얼굴
    newShape_6->position[0] = x ;
    newShape_6->position[1] = y - 0.1f;
    newShape_6->position[2] = z;
    newShape_6->size = 0.05f;
    newShape_6->num = 3;
    newShape_6->color[0] = 0;
    newShape_6->color[1] = 0;
    newShape_6->color[2] = 1;
    newShape_6->generateFaces(); // 정점 데이터 초기화
    shapes.push_back(newShape_6);
   
    glutPostRedisplay();
}
void frontOpen(int value) {
    if (!frontFaceOpen) {
        return;
    }
    frontFaceAngel += 1.0f;
    if (frontFaceAngel >= 90.0f) {
        frontFaceAngel = 90.0f;  // Reset to avoid overflow
        return;
    }
    glutPostRedisplay();
    glutTimerFunc(12, frontOpen, 0);
}
void walking(int value) {
    if (!isWalking) {
        return;
    }
    if (robot_dir == 6) {
        rotationAngleY += 10.0f;
        if (rotationAngleY >= 90) { //오른쪽 이동
            rotationAngleY = 90;
            movingX += speed;
            if (value == 0) {
                rotationAngleZ += speed * 100.0f;
            }
            else if (value == 1) {
                rotationAngleZ -= speed * 100.0f;
            }
            if (movingX >= 0.9f) {
                robot_dir = 4;
            }
        }
    }
    else if (robot_dir == 4) {  //왼쪽 이동
       
        rotationAngleY -= 10.0f;
        if (rotationAngleY <= -90) {
            rotationAngleY = -90;
            movingX -= speed;
            if (value == 0) {
                rotationAngleZ += speed * 100.0f;
            }
            else if (value == 1) {
                rotationAngleZ -= speed * 100.0f;
                
            }
            if (movingX <= -0.9f) {
                robot_dir = 6;
            }
        }
    }
    else if (robot_dir == 2) { //아래로 이동
        rotationAngleZ = 0.0f;
        if (rotationAngleY >= 0) {
            rotationAngleY -= 10.0f;
            if (rotationAngleY <= 0) {
                rotationAngleY = 0;
                movingZ += speed;
            }
        }
        else if (rotationAngleY <= 0) {
            rotationAngleY += 10.0f;
            if (rotationAngleY >= 0) {
                rotationAngleY = 0;
                movingZ += speed;
            }
        }
        if (value == 0) {
            rotationAngleX += speed * 100.0f;
        }
        else if (value == 1) {
            rotationAngleX -= speed * 100.0f;

        }
        if (movingZ >= 0.9f) {
            robot_dir = 8;
        }
    }
    else if (robot_dir == 8) { //아래로 이동
        rotationAngleZ = 0.0f;
        
            rotationAngleY += 10.0f;
            if (rotationAngleY >= 180) {
                rotationAngleY = 180;
                movingZ -= speed;
            }
        if (value == 0) {
            rotationAngleX += speed*100.0f;
        }
        else if (value == 1) {
            rotationAngleX -= speed * 100.0f;

        }
        if (movingZ <= -0.9f) {
            robot_dir = 2;
        }
    }

    if (rotationAngleZ >= 30||rotationAngleX>=30) {
        value = 1;
    }
    else if (rotationAngleZ <= -30||rotationAngleX<=-30) {
        value = 0;
    }
    glutPostRedisplay();
    glutTimerFunc(12, walking, value);
}
void jumping(int value) {
    if (!isJumping) {
        return;
    }
    if (value == 0) {
        movingY += 0.01f;
        if (movingY >= 0.5f) {
            value = 1;
        }
    }
    else {
        movingY -= 0.01f;
        if ( ((movingX >= ob_1.posittion[0] - 0.2f && movingX <= ob_1.posittion[0] + 0.2f) && (movingZ >= ob_1.posittion[2] - 0.2f && movingZ <= ob_1.posittion[2] + 0.2f))||
            ((movingX >= ob_2.posittion[0] - 0.2f && movingX <= ob_2.posittion[0] + 0.2f) && (movingZ >= ob_2.posittion[2] - 0.2f && movingZ <= ob_2.posittion[2] + 0.2f))||
            ((movingX >= ob_3.posittion[0] - 0.2f && movingX <= ob_3.posittion[0] + 0.2f) && (movingZ >= ob_3.posittion[2] - 0.2f && movingZ <= ob_3.posittion[2] + 0.2f))  ) {
            std::cout << "obs";
            if (movingY <= 0.2f) {
                movingY = 0.2f;
            }
        }
        else {
            if (movingY <= 0.0f) {
                movingY = 0;
                isJumping = 0;
            }
        }
        
    }
    glutPostRedisplay();
    glutTimerFunc(12, jumping, value);
}

void Cleanup() {
    // 할당된 Shape 객체 삭제
    for (auto shape : shapes) {
        delete shape;
    }
    shapes.clear();
}
void drawObjects() {
    // Draw cube, pyramid, and line
    make_cube(0, 0, 0);
    make_clane(0, 0, 0);
}


