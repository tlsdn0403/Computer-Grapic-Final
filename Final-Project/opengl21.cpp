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
    std::vector<std::vector<GLfloat>> faces; // 6���� ���� ����
    std::vector<std::vector<GLfloat>> vertexColors;//���� ���� �ϴ� ����

};

class CubeShape : public Shape {
public:
    std::vector<std::vector<GLfloat>> faces; // ���� ���� 
    std::vector<std::vector<GLfloat>> vertexColors;//���� ���� �ϴ� ����
    GLfloat frontRotatingAngel = 0.0f;
    CubeShape() {
        faces.resize(6); // 6���� ���� ���� ���� �Ҵ�
        vertexColors.resize(6);
    }
    void generateFaces() {

        // �� ���� ���� �����͸� �ʱ�ȭ
        // Front Face (Z+)
        faces[0] = {  // �ٴ�
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
        faces[1] = {  // �� ����
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
        faces[2] = {  // �ո�
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
        faces[3] = {  // �� ����
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
        faces[4] = {  // �޸�
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
        faces[5] = {  // ����
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
            glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); // vbo[1]�� ���� ���� ����
            glBufferSubData(GL_ARRAY_BUFFER, 0, vertexColors[i].size() * sizeof(GLfloat), vertexColors[i].data());

            

            glm::mat4 Tx = glm::mat4(1.0f);
            Tx = glm::translate(Tx, glm::vec3(0.0 , 0.0, 0.0)); // �̵����



            glm::mat4 Rz = glm::mat4(1.0f);
            Rz = glm::rotate(Rz, glm::radians(10.0f), glm::vec3(1.00, 0.00, 0.0)); //�⺻���� ȸ�� ���

            glm::mat4 Ry = glm::mat4(1.0f);
            Ry = glm::rotate(Ry, glm::radians(rotateMiddle), glm::vec3(0.00, 1.00, 0.0)); //�⺻���� ȸ�� ���


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
//�κ��� �� �ٸ� �� �� �׸��� Ŭ������ 
class RobotLeg: public Shape {
public:
    std::vector<std::vector<GLfloat>> faces; // ���� ���� 
    std::vector<std::vector<GLfloat>> vertexColors;//���� ���� �ϴ� ����
    GLfloat rotateY = rotationAngleY;
    RobotLeg() {
        faces.resize(6); // 6���� ���� ���� ���� �Ҵ�
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
    //���� num=2,3��
    void draw(GLuint shaderProgramID, GLuint vbo[]) {
        for (int i = 0; i < 6; i++) {
            if (i >= faces.size()) {
                std::cerr << "Error: faces vector index out of range." << std::endl;
                continue;
            }
            glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
            glBufferSubData(GL_ARRAY_BUFFER, 0, faces[i].size() * sizeof(GLfloat), faces[i].data());
            glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); // vbo[1]�� ���� ���� ����         
            glBufferSubData(GL_ARRAY_BUFFER, 0, vertexColors[i].size() * sizeof(GLfloat), vertexColors[i].data());



            glm::mat4 Tx = glm::mat4(1.0f);
            Tx = glm::translate(Tx, glm::vec3(0.0 + movingX, 0.0+ movingY, 0.0 + movingZ)); // �̵����
            
            glm::mat4 Ty_1 = glm::mat4(1.0f);
            glm::mat4 Ty_2 = glm::mat4(1.0f);
            if (num == 0 || num == 1) {
                Ty_1 = glm::translate(Ty_1, glm::vec3(0.0, 0.6, 0.0)); // �̵����
                Ty_2 = glm::translate(Ty_2, glm::vec3(0.0, -0.6, 0.0)); // �̵����
            }
            else {
                Ty_1 = glm::translate(Ty_1, glm::vec3(0.0, 0.2, 0.0)); // �̵����
                Ty_2 = glm::translate(Ty_2, glm::vec3(0.0, -0.2, 0.0)); // �̵����
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
    std::vector<std::vector<GLfloat>> faces; // ���� ���� 
    std::vector<std::vector<GLfloat>> vertexColors;//���� ���� �ϴ� ����
    GLfloat rotateY = rotationAngleY;
    RobotBody() {
        faces.resize(6); // 6���� ���� ���� ���� �Ҵ�
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
            glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); // vbo[1]�� ���� ���� ����         
            glBufferSubData(GL_ARRAY_BUFFER, 0, vertexColors[i].size() * sizeof(GLfloat), vertexColors[i].data());

        
            glm::mat4 Rx = glm::mat4(1.0f);
            glm::mat4 Tx = glm::mat4(1.0f);
            Tx = glm::translate(Tx, glm::vec3(0.0 + movingX, 0.0+movingY, 0.0 + movingZ)); // �̵����




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
    std::vector<std::vector<GLfloat>> faces; // ���� ���� 
    std::vector<std::vector<GLfloat>> vertexColors;//���� ���� �ϴ� ����
    GLfloat rotateY = rotationAngleY;
    RobotFace() {
        faces.resize(6); // 6���� ���� ���� ���� �Ҵ�
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
            glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); // vbo[1]�� ���� ���� ����         
            glBufferSubData(GL_ARRAY_BUFFER, 0, vertexColors[i].size() * sizeof(GLfloat), vertexColors[i].data());


            glm::mat4 Rx = glm::mat4(1.0f);
            glm::mat4 Tx = glm::mat4(1.0f);
            Tx = glm::translate(Tx, glm::vec3(0.0 + movingX, 0.0+ movingY, 0.0 + movingZ)); // �̵����




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
GLfloat aspect = windowWidth / windowHeight; //��Ⱦ��


// Main function
int main(int argc, char** argv) {
    //--- Create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL Shapes Example");
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //--- GLEW �ʱ�ȭ�ϱ�
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
    glutPostRedisplay(); // ȭ�� �ٽ� �׸���
    atexit(Cleanup); //�޸� ���� ���� (new�� �Ҵ�� ��ü delete)

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


    for (auto shape : shapes) {  // shapes ���Ϳ� ������ �������� ��� �׸��� ��  (�� ���� Ŭ�������� draw �Լ��� �־����)
        shape->draw(shaderProgramID, vboArr);
    }

    glutSwapBuffers();
}




void Reshape(int w, int h) {

    glViewport(0, 0, w, h);
}

// �������� ���� �ʱ�ȭ
void InitBuffer() {
    glGenVertexArrays(1, &vao); //VAO �����ϰ� �Ҵ�
    glBindVertexArray(vao);  // VAO ���ε��ϱ�
    glGenBuffers(2, vboArr); // 2���� VBO �Ҵ�(���������� ������ �Ҵ������� 1���� �ʿ�)


    //posittion
    glBindBuffer(GL_ARRAY_BUFFER, vboArr[0]); //VBO ���ε�
    glBufferData(GL_ARRAY_BUFFER, 108 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW); //�ִ� (6���� ����*3���� ��ǥ)  (36 * 3 = 108 floats)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vboArr[1]);
    //--- ���� colors���� ���ؽ������������Ѵ�.
    //--- colors �迭�� ������: 9 *float 
    glBufferData(GL_ARRAY_BUFFER, 108 * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
    //--- ������attribute �ε���1���������Ѵ�: ���ؽ���3*float
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //--- attribute �ε��� 1���� ��밡���ϰ���.
    glEnableVertexAttribArray(1);
}

//���̴� ���α׷� �����ϱ�
void make_shaderProgram() {
    //���ؽ��� �����׸�Ʈ ���̴� �����
    make_vertexShaders();
    make_fragmentShaders();

    // ���̴� ���α׷� �����
    shaderProgramID = glCreateProgram();

    glAttachShader(shaderProgramID, vertexShader);
    glAttachShader(shaderProgramID, fragmentShader);
    glLinkProgram(shaderProgramID);

    // ����üũ
    GLint success;
    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(shaderProgramID, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        exit(EXIT_FAILURE);
    }

    // ���̴� �����ϱ�
    glDeleteShader(vertexShader); //-���̴���ü�� ���̴����α׷��� ��ũ��������,���̴���ü ��ü�� ��������
    glDeleteShader(fragmentShader);

    // Shader program ���
    glUseProgram(shaderProgramID);
}


void make_vertexShaders() {
    vertexSource = filetobuf("vertex.glsl");
    if (!vertexSource) {
        std::cerr << "Failed to load vertex shader." << std::endl;
        exit(EXIT_FAILURE);
    }

    // ���ؽ� ���̴� ��ü �����
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //  ���̴��ڵ带 ���̴� ��ü�� �ֱ�
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
    //�����׸�Ʈ �����б�
    fragmentSource = filetobuf("fragment.glsl");
    if (!fragmentSource) {
        std::cerr << "Failed to load fragment shader." << std::endl;
        exit(EXIT_FAILURE);
    }

    // �����׸�Ʈ ��ü �����
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // ���̴� �ڵ� ���̴� ��ü�� �ֱ�
    glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, 0);
    // �����׸�Ƽ ���̴� ������
    glCompileShader(fragmentShader);
    // ������ ���� üũ
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
  
    glutPostRedisplay();
}



void Keyboard(unsigned char key, int x, int y) {

    switch (key)
    {

    case'w': {
        isWalking = !isWalking;
        robot_dir = 8;
        glutTimerFunc(12, walking, 0);
        glutPostRedisplay();
        break;
    }
    case'a': {
        movingX -= 0.1f;
        glutPostRedisplay();
        break;
    }
    case'd': {
        movingX += 0.1f;
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
    case'j':{
        isJumping = true;
        glutTimerFunc(12, jumping, 0);
        break;
    }
    default:
        break;
    }
    glutPostRedisplay(); // ȭ�� �ٽ� �׸��� ��û
}


void make_robot(GLfloat x, GLfloat y, GLfloat z) {
    Shape* newShape = new RobotBody(); //�Ʒ���ü
    newShape->position[0] = x;
    newShape->position[1] = y-0.4f;
    newShape->position[2] = z;
    newShape->size = 0.1f;
    newShape->color[0] = 0;
    newShape->color[1] = 0;
    newShape->color[2] = 1;
    newShape->generateFaces(); // ���� ������ �ʱ�ȭ
    shapes.push_back(newShape);

    Shape* newShape_2 = new RobotLeg(); //�޴ٸ�
    newShape_2->position[0] = x-0.05f;
    newShape_2->position[1] = y-0.6f;
    newShape_2->position[2] = z;
    newShape_2->num = 1;
    newShape_2->size = 0.02f;
    newShape_2->color[0] = 0;
    newShape_2->color[1] = 1;
    newShape_2->color[2] = 0;
    newShape_2->generateFaces(); // ���� ������ �ʱ�ȭ
    shapes.push_back(newShape_2);

    Shape* newShape_3 = new RobotLeg(); //�����ٸ�
    newShape_3->position[0] = x + 0.05f;
    newShape_3->position[1] = y - 0.6f;
    newShape_3->position[2] = z;
    newShape_3->size = 0.02f;
    newShape_3->color[0] = 1;
    newShape_3->color[1] = 1;
    newShape_3->color[2] = 0;
    newShape_3->generateFaces(); // ���� ������ �ʱ�ȭ
    shapes.push_back(newShape_3);


    Shape* newShape_4 = new RobotLeg(); //����
    newShape_4->position[0] = x - 0.11f;
    newShape_4->position[1] = y - 0.2f;
    newShape_4->position[2] = z;
    newShape_4->num = 2;
    newShape_4->size = 0.01f;
    newShape_4->color[0] = 1;
    newShape_4->color[1] = 0;
    newShape_4->color[2] = 1;
    newShape_4->generateFaces(); // ���� ������ �ʱ�ȭ
    shapes.push_back(newShape_4);

    Shape* newShape_5 = new RobotLeg(); //������
    newShape_5->position[0] = x + 0.11f;
    newShape_5->position[1] = y - 0.2f;
    newShape_5->position[2] = z;
    newShape_5->size = 0.01f;
    newShape_5->num = 3;
    newShape_5->color[0] = 0;
    newShape_5->color[1] = 1;
    newShape_5->color[2] = 1;
    newShape_5->generateFaces(); // ���� ������ �ʱ�ȭ
    shapes.push_back(newShape_5);

    Shape* newShape_6 = new RobotFace(); //��
    newShape_6->position[0] = x ;
    newShape_6->position[1] = y - 0.1f;
    newShape_6->position[2] = z;
    newShape_6->size = 0.05f;
    newShape_6->num = 3;
    newShape_6->color[0] = 0;
    newShape_6->color[1] = 0;
    newShape_6->color[2] = 1;
    newShape_6->generateFaces(); // ���� ������ �ʱ�ȭ
    shapes.push_back(newShape_6);
   
    glutPostRedisplay();
}
void walking(int value) {
    if (!isWalking) {
        return;
    }
    rotationAngleZ = 0.0f;
    rotationAngleY += 10.0f;
    if (rotationAngleY >= 180) {
        rotationAngleY = 180;
    }
    if (value == 0) {
        rotationAngleX += speed * 200.0f;
    }
    else if (value == 1) {
        rotationAngleX -= speed * 200.0f;
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
        //�κ� ����
        movingY += 0.01f;
        if (movingY >= 0.5f) {
            //�κ��� y��ǥ�� ������ǥ�̸� �߶��ϵ���(���� ��)
            value = 1;
        }
    }
    else {
        //����
        movingY -= 0.01f;
        if (movingY <= 0.0f) {
            movingY = 0;
            isJumping = 0;
        } 
    }
    glutPostRedisplay();
    glutTimerFunc(12, jumping, value);
}

void Cleanup() { //�ϴ� ������ �Ⱦ��� 
    // �Ҵ�� Shape ��ü ����
    for (auto shape : shapes) {
        delete shape;
    }
    shapes.clear();
}
void drawObjects() {
    // ������Ʈ�� �׸��� �Լ�
    make_cube(0, 0, 0);
    make_robot(0, 0, 0);
}

