#include "CubeShape.h"

CubeShape::CubeShape() {
    faces.resize(6); // 6개의 면을 위한 공간 할당
    vertexColors.resize(6);
}
void CubeShape::generateFaces() {

    // 각 면의 정점 데이터를 초기화
    // Front Face (Z+)
    faces[0] = {  // 바닥
    position[0] - size, position[1] - size , position[2] + size,  // v1 (Top-left)
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

void CubeShape::draw(GLuint shaderProgramID, GLuint vbo[]) {
    for (int i = 0; i < 6; i++) {
        if (i >= faces.size()) {
            std::cerr << "Error: faces vector index out of range." << std::endl;
            continue;
        }


        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, faces[i].size() * sizeof(GLfloat), faces[i].data());
        glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertexColors[i].size() * sizeof(GLfloat), vertexColors[i].data());

        glm::mat4 Tx = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0));

        glm::mat4 modelMatrix = Tx;

        GLuint mvpLocation = glGetUniformLocation(shaderProgramID, "uMVP");
        glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
}