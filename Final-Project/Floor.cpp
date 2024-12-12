#include "Floor.h"
#include"FenceShape.h"

Floor::Floor() {
    faces.resize(6); // 6개의 면을 위한 공간 할당
    vertexColors.resize(6);
    texCoords.resize(6);
}
void Floor::generateFaces() {

    // 각 면의 정점 데이터를 초기화
    // Front Face (Z+)
    faces[0] = {  // 바닥
    position[0] - size, position[1] , position[2] + size+ length,  // v1 (Top-left)
    position[0] + size, position[1]  , position[2] + size+ length,  // v2 (Top-right)
    position[0] - size, position[1] , position[2] - (size+ length),  // v3 (Bottom-left)
    position[0] + size, position[1]  , position[2] - (size+ length)   // v4 (Bottom-right)
    };

  

    texCoords[0] = {
          0.0f , 0.0f , // 아래 왼쪽
          1.0f ,  0.0f, // 아래 오른쪽
          0.0f, 1.0f, // 위 왼쪽
          1.0f , 1.0f , // 위 오른쪽
    };

}

void Floor::draw(GLuint shaderProgramID, GLuint vbo[], GLuint textureID[]) {
    glUseProgram(shaderProgramID);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, textureID[2]);
    setSelectedTexture(shaderProgramID, 2);
    glUniform1i(glGetUniformLocation(shaderProgramID, "Texture2"), 2);
    for (int i = 0; i < 6; i++) {
        if (i >= faces.size()) {
            std::cerr << "Error: faces vector index out of range." << std::endl;
            continue;
        }
        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, faces[i].size() * sizeof(GLfloat), faces[i].data());
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertexColors[i].size() * sizeof(GLfloat), vertexColors[i].data());
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, texCoords[i].size() * sizeof(GLfloat), texCoords[i].data());
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(2);

        glm::mat4 modelMatrix = createTransformMatrix();

        GLuint mvpLocation = glGetUniformLocation(shaderProgramID, "uMVP");
        glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); // Adjust based on your drawing mode
    }
}
glm::mat4 Floor::createTransformMatrix() {
    glm::mat4 Tx = glm::translate(glm::mat4(1.0f), glm::vec3(moving_Box_X, moving_Box_Y, moving_Box_Z));
    glm::mat4 Ty_1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.6f, 0.0f));
    glm::mat4 Ty_2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.6f, 0.0f));
    glm::mat4 Ry = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngleY), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Rx = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngleX), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 Rz = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngleZ), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 TR = Tx * Ty_1 * Ry * Rx * Rz * Ty_2;
    return TR;
}