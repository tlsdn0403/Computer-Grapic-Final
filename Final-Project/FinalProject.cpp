#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include"stb_image.h"
#include <cstdlib>
#include <random>
#include <fstream>
#include <vector>
#include"shape.h"
#include"CubeShape.h"
#include"FenceShape.h"
#include"Box.h"
#include"Food.h"
#include"Floor.h"
#include"longFence.h"
#include"glmFiles.hpp"

std::random_device rd;  // 시드로 사용할 난수 생성 장치
std::mt19937 gen(rd());
std::uniform_int_distribution<int> RandSpawn(1, 9);
std::uniform_int_distribution<int> RandFoodLocate(1, 3);


bool projection, rotate_mid, rotateBarrel, rotateArm , frontFaceOpen,isWalking,isJumping = false;
bool isDepthTest = false;
bool gamePlay = false;
GLuint textureID[10];
GLfloat rotationAngleX = 0;
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
int TimeCount = 0;
int SpawnTime = 250;
int robot_dir = 0;
int FenceCount = 0;
int LongFenceCount = 0;
int BoxCount = 0;
int FoodCount = 0;
float ObjSpeed = 0.02;
void drawScene();
void initTextures(GLuint shaderProgramID);
void make_Box(GLfloat x, GLfloat y, GLfloat z);
void make_Fence(GLfloat x, GLfloat y, GLfloat z);
void make_LongFence(GLfloat x, GLfloat y, GLfloat z);
void make_Food(GLfloat x, GLfloat y, GLfloat z);
void make_Floor(GLfloat x, GLfloat y, GLfloat z);
void make_Box(GLfloat x, GLfloat y, GLfloat z, GLfloat Length);
void walking(int value);
void jumping(int value);
void Reshape(int w, int h);
void InitBuffer();
void drawObjects(int i, int j);
void make_shaderProgram();
void make_vertexShaders();
void make_fragmentShaders();
void Keyboard(unsigned char key, int x, int y);
void loadTexture(GLuint textureID, const char* filePath, GLenum textureUnit, const char* uniformName, GLuint shaderProgramID);
void Cleanup();
void TimerFunction(int value);
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
//로봇의 팔 다리 얼굴 을 그리는 클래스들 
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
        float heightMultiplier = 15.0f; // Make the cube longer along the y-axis

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
            glUniform1i(glGetUniformLocation(shaderProgramID, "selectedTexture"), 11);
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
            glUniform1i(glGetUniformLocation(shaderProgramID, "selectedTexture"), 11);
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
            glUniform1i(glGetUniformLocation(shaderProgramID, "selectedTexture"), 11);
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



GLchar* vertexSource, * fragmentSource;
GLuint vertexShader, fragmentShader;
GLuint shaderProgramID;
GLuint vao, vboArr[3];
std::vector<Shape*> shapes;
std::vector<FenceShape*> Fence_shapes;
std::vector<Box*> Box_shapes;
std::vector<Food*> Food_shapes;
std::vector<Floor*> Floor_shapes;
std::vector<longFence*> LongFence_shapes;


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
    make_Box(1, 0, -0, 1);
    drawObjects(1, 0);
    initTextures(shaderProgramID);
    glutDisplayFunc(drawScene);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);
    glutPostRedisplay(); // 화면 다시 그리기
    atexit(Cleanup); //메모리 누수 방지 (new로 할당된 객체 delete)

    glutMainLoop();
    return 0;
}

void loadTexture(GLuint textureID, const char* filePath, GLenum textureUnit, const char* uniformName, GLuint shaderProgramID) {
    // Activate the texture unit
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture wrapping/filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load and generate texture
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);

    if (data) {
        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        std::cout << "Loaded texture: " << filePath << std::endl;
    }
    else {
        std::cerr << "Failed to load texture: " << filePath << std::endl;
    }

    // Free image data
    stbi_image_free(data);

    // Set the texture uniform in the shader
    glUseProgram(shaderProgramID);
    GLint uniformLocation = glGetUniformLocation(shaderProgramID, uniformName);
    if (uniformLocation != -1) {
        glUniform1i(uniformLocation, textureUnit - GL_TEXTURE0); // Map texture unit to uniform
    }
    else {
        std::cerr << "Uniform '" << uniformName << "' not found in shader!" << std::endl;
    }
}

void initTextures(GLuint shaderProgramID) {
    // Generate 10 texture IDs
    glGenTextures(10, textureID);

    // Load textures into the texture array
    loadTexture(textureID[0], "Fence.png", GL_TEXTURE0, "Texture0", shaderProgramID); //펜스 사진
    loadTexture(textureID[1], "chocopi.png", GL_TEXTURE1, "Texture1", shaderProgramID); //음식사진
    loadTexture(textureID[2], "sky.jpg", GL_TEXTURE2, "Texture2", shaderProgramID); //바닥 사진 바꿀거면 sky.jpg대신 다른 사진 넣으면 됨
    loadTexture(textureID[3], "Box.png", GL_TEXTURE3, "Texture3", shaderProgramID); //3번 텍스처에 박스 저장

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

    glm::vec3 cameraPos = glm::vec3(0.0f + cameraX, 1.0f, 2.0f + cameraZ);
    glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f , 0.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
    unsigned int viewLocation = glGetUniformLocation(shaderProgramID, "viewTransform");
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);


    for (auto shape : shapes) {  // shapes 벡터에 저장한 도형들을 모두 그리는 거  (각 도형 클래스마다 draw 함수를 넣어놨음)
        shape->draw(shaderProgramID, vboArr);
    }
    for (auto shape : LongFence_shapes) {
            shape->draw(shaderProgramID, vboArr, textureID);
    }
    for (auto shape : Fence_shapes) {  // 팬스 벡터에 저장한 도형들을 모두 그리는 거  (각 도형 클래스마다 draw 함수를 넣어놨음)
            shape->draw(shaderProgramID, vboArr, textureID);
    }
    for (auto shape : Box_shapes) {  // 박스 
            shape->draw(shaderProgramID, vboArr, textureID);
    }
    for (auto shape : Food_shapes) {  // 음식
            shape->draw(shaderProgramID, vboArr, textureID);
    }
    for (auto shape : Floor_shapes) {  // 바닥 
        shape->draw(shaderProgramID, vboArr, textureID);
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
    glGenBuffers(3, vboArr); // 2개의 VBO 할당(유니폼으로 색상을 할당함으로 1개만 필요)


    //posittion
    glBindBuffer(GL_ARRAY_BUFFER, vboArr[0]); //VBO 바인드
    glBufferData(GL_ARRAY_BUFFER, 108 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW); //최대 (6개의 정점*3개의 좌표)  (36 * 3 = 108 floats)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vboArr[1]);
    //--- 변수 colors에서 버텍스색상을복사한다.
    //--- colors 배열의 사이즈: 9 *float 
    glBufferData(GL_ARRAY_BUFFER, 108 * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, vboArr[2]);
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
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


void make_Fence(GLfloat x, GLfloat y, GLfloat z) {
    FenceShape* newShape = new FenceShape();
    newShape->position[0] = x;
    newShape->position[1] = y;
    newShape->position[2] = z;
    newShape->size = 0.1f;
    newShape->generateFaces(); // 정점 데이터 초기화
    Fence_shapes.push_back(newShape);
  
    glutPostRedisplay();
}
void make_LongFence(GLfloat x, GLfloat y, GLfloat z) {
    longFence* newShape = new longFence();
    newShape->position[0] = x;
    newShape->position[1] = y;
    newShape->position[2] = z;
    newShape->size = 0.1f;
    newShape->generateFaces(); // 정점 데이터 초기화
    LongFence_shapes.push_back(newShape);

    glutPostRedisplay();
}
void make_Box(GLfloat x, GLfloat y, GLfloat z) {
    Box* newShape = new Box();
    newShape->position[0] = x;
    newShape->position[1] = y;
    newShape->position[2] = z;
    newShape->size = 0.1f;
    newShape->generateFaces(); // 정점 데이터 초기화
    Box_shapes.push_back(newShape);

    glutPostRedisplay();
}

void make_Food(GLfloat x, GLfloat y, GLfloat z) {
    Food* newShape = new Food();
    newShape->position[0] = x;
    newShape->position[1] = y;
    newShape->position[2] = z;
    newShape->size = 0.1f; //사이즈 정해줄 수 있음
    newShape->generateFaces(); // 정점 데이터 초기화
    Food_shapes.push_back(newShape);

    glutPostRedisplay();
}
void make_Floor(GLfloat x, GLfloat y, GLfloat z) {
    Floor* newShape = new Floor();
    newShape->position[0] = x;
    newShape->position[1] = y;
    newShape->position[2] = z;
    newShape->length = 3.0f;//바닥 길이 정해주기 (Z축 만 건들임)
    newShape->size = 3; //사이즈 정해줄 수 있음
    newShape->generateFaces(); // 정점 데이터 초기화
    Floor_shapes.push_back(newShape);

    glutPostRedisplay();
}
void make_Box(GLfloat x, GLfloat y, GLfloat z, GLfloat Length) {
    Box* newShape = new Box();
    newShape->position[0] = x;
    newShape->position[1] = y;
    newShape->position[2] = z;
    newShape->size = 0.3f; //사이즈 정해줄 수 있음
    newShape->length = 1.0f;
    newShape->generateFaces(); // 정점 데이터 초기화
    Box_shapes.push_back(newShape);

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
        if(movingX != -1.0)
            movingX -= 1.0;
        glutPostRedisplay();
        break;
    }
    case'd': {
        if (movingX != 1.0)
            movingX += 1.0;
        glutPostRedisplay();
        break;
    }
    case 'z': {
        cameraZ += 0.1;
        glutPostRedisplay();
        break;
    }case 'Z': {
        cameraZ -= 0.1;
        if (cameraZ <= -3.0) {
            cameraZ = -3.0;
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
    case's':{
        //s한 번 누르면 gamePlay가 참 다시 누르면 거짓
        gamePlay = !gamePlay;
        glutTimerFunc(30, TimerFunction, 0); // 타이머함수 재 설정;
        break;
    }
    default:
        break;
    }
    glutPostRedisplay(); // 화면 다시 그리기 요청
}


void make_robot(GLfloat x, GLfloat y, GLfloat z) {
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
void walking(int value) { //로봇 걷는 함수
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
        //로봇 점프
        movingY += 0.01f;
        if (movingY >= 0.5f) {
            //로봇의 y좌표가 일정좌표이면 추락하도록(점프 끝)
            value = 1;
        }
    }
    else {
        //착지
        movingY -= 0.01f;
        if (movingY <= 0.0f) {
            movingY = 0;
            isJumping = 0;
        } 
    }
    glutPostRedisplay();
    glutTimerFunc(12, jumping, value);
}

void Cleanup() { //일단 지금은 안쓰임 
    // 할당된 Shape 객체 삭제
    for (auto shape : shapes) {
        delete shape;
    }
    shapes.clear();
}
void drawObjects(int i, int j) {
    // 오브젝트들 그리는 함수
    if (i == 1) {
        make_Fence(-1, 0, -10.0);
        ++FenceCount;
        make_LongFence(1, 1, -10.0);
        ++LongFenceCount;
    }
    else if (i == 2) {
        make_Fence(0, 0, -10.0);
        ++FenceCount;
        make_Box(-1, 0, -10.0);
        ++BoxCount;
    }
    else if (i == 3) {    
        make_Fence(1, 0, -10.0);
        ++FenceCount;
        make_Box(0, 0, -10.0);
        ++BoxCount;
    }
    else if (i == 4) {
        make_LongFence(-1, 1, -10.0);
        ++LongFenceCount;
        make_Box(1, 0, -10.0);
        ++BoxCount;
    }
    else if (i == 5) {
        make_LongFence(0, 1, -10.0);
        ++LongFenceCount;
        make_Fence(-1, 0, -10.0);
        ++FenceCount;
    }
    else if (i == 6) {
        make_LongFence(1, 1, -10.0);
        ++LongFenceCount;
        make_Fence(0, 0, -10.0);
        ++FenceCount;
    }
    else if (i == 7) {
        make_Box(-1, 0, -10.0);
        ++BoxCount;
        make_Fence(1, 0, -10.0);
        ++FenceCount;
    }
    else if (i == 8) {
        make_Box(0, 0, -10.0);
        ++BoxCount;
        make_LongFence(-1, 1, -10.0);
        ++LongFenceCount;
    }
    else if (i == 9) {
        make_Box(1, 0, -10.0);
        ++BoxCount;
        make_LongFence(0, 1, -10.0);
        ++LongFenceCount;
    }
    if (j == 1){
        make_Food(-1, -0.5, -8.0);
        ++FoodCount;
    }
    else if (j == 2){
        make_Food(0, -0.5, -8.0);
        ++FoodCount;
    }
    else if (j == 3){
        make_Food(1, -0.5, -8.0);
        ++FoodCount;
    }
    make_robot(0, 0, 0);
    make_Floor(0, -1.0, -5.0);
}

void TimerFunction(int value) { // 시간이 지남에 따라 객체들 이동
    if (!gamePlay) { //참이면 실행 거짓이면 종료
        return;
    }
    ++TimeCount;
    if (TimeCount % SpawnTime == 0) {
        drawObjects(RandSpawn(gen), RandFoodLocate(gen));
        SpawnTime -= 10;
        ObjSpeed += 0.005;
    }
    for (int i = FenceCount - 1; i >= 0; --i) {
        if (Fence_shapes[i]->moving_fence_Z + -10.00 >= 0.5) {
            Fence_shapes.erase(Fence_shapes.begin() + i);
            --FenceCount;
        }
        else
            Fence_shapes[i]->moving_fence_Z += ObjSpeed;
    }
    for (int i = FoodCount - 1; i >= 0; --i) {
        if (Food_shapes[i]->moving_Box_Z + -10.00 >= 0.5) {
            Food_shapes.erase(Food_shapes.begin() + i);
            --FoodCount;
        }
        else
            Food_shapes[i]->moving_Box_Z += ObjSpeed;
    }
    for (int i = LongFenceCount - 1; i >= 0; --i) {
        if (LongFence_shapes[i]->moving_fence_Z + -10.00 >= 0.5) {
            LongFence_shapes.erase(LongFence_shapes.begin() + i);
            --LongFenceCount;
        }
        else
            LongFence_shapes[i]->moving_fence_Z += ObjSpeed;
    }
    for (int i = BoxCount - 1; i >= 0; --i) {
        if (Box_shapes[i]->moving_Box_Z + -10.00 >= 0.5) {
            Box_shapes.erase(Box_shapes.begin() + i);
            --BoxCount;
        }
        else
            Box_shapes[i]->moving_Box_Z += ObjSpeed;
    }
    glutSwapBuffers(); //--- 화면에 출력하기
    glutPostRedisplay(); // 화면 재 출력
    glutTimerFunc(30, TimerFunction, 0); // 타이머함수 재 설정
}
