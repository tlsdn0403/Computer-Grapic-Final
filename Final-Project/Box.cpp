#include "Box.h"
#include"FenceShape.h"

Box::Box() {
    faces.resize(6); // 6���� ���� ���� ���� �Ҵ�
    vertexColors.resize(6);
    texCoords.resize(6);
}
void Box::generateFaces() {

    // �� ���� ���� �����͸� �ʱ�ȭ
    // Front Face (Z+)
    faces[0] = {  // �ٴ�
    position[0] - size, position[1] - size , position[2] + size,  // v1 (Top-left)
    position[0] + size, position[1] - size , position[2] + size,  // v2 (Top-right)
    position[0] - size, position[1] - size , position[2] - size,  // v3 (Bottom-left)
    position[0] + size, position[1] - size , position[2] - size   // v4 (Bottom-right)
    };

    faces[1] = {  // �� ����
    position[0] + size, position[1] - size , position[2] + size,  // v1 (Top-left)
    position[0] + size, position[1] - size, position[2] - size,  // v2 (Top-right)
    position[0] + size, position[1] + size , position[2] + size,  // v3 (Bottom-left)
    position[0] + size, position[1] + size , position[2] - size   // v4 (Bottom-right)
    };


    faces[2] = {  // �ո�
    position[0] - size, position[1] - size , position[2] + size,  // v1 (Top-left)
    position[0] + size, position[1] - size, position[2] + size,  // v2 (Top-right)
    position[0] - size, position[1] + size , position[2] + size,  // v3 (Bottom-left)
    position[0] + size, position[1] + size , position[2] + size   // v4 (Bottom-right)
    };


    faces[3] = {  // �� ����
    position[0] - size, position[1] - size, position[2] + size,  // v1 (Top-left)
    position[0] - size, position[1] - size, position[2] - size,  // v2 (Top-right)
    position[0] - size, position[1] + size , position[2] + size,  // v3 (Bottom-left)
    position[0] - size, position[1] + size , position[2] - size   // v4 (Bottom-right)
    };


    faces[4] = {  // �޸�
    position[0] - size, position[1] - size, position[2] - size,  // v1 (Top-left)
    position[0] + size, position[1] - size, position[2] - size,  // v2 (Top-right)
    position[0] - size, position[1] + size , position[2] - size,  // v3 (Bottom-left)
    position[0] + size, position[1] + size , position[2] - size   // v4 (Bottom-right)
    };


    faces[5] = {  // ����
    position[0] - size, position[1] + size, position[2] + size,  // v1 (Top-left)
    position[0] + size, position[1] + size , position[2] + size,  // v2 (Top-right)
    position[0] - size, position[1] + size , position[2] - size,  // v3 (Bottom-left)
    position[0] + size, position[1] + size, position[2] - size   // v4 (Bottom-right)
    };




    texCoords[0] = {
          0.0f , 0.0f , // �Ʒ� ����
          1.0f ,  0.0f, // �Ʒ� ������
          0.0f, 1.0f, // �� ����
          1.0f , 1.0f , // �� ������
    };
    texCoords[1] = {
           0.0f , 0.0f , // �Ʒ� ����
           1.0f ,  0.0f, // �Ʒ� ������
           0.0f, 1.0f, // �� ����
           1.0f , 1.0f , // �� ������
    };
    texCoords[2] = {
           0.0f , 0.0f , // �Ʒ� ����
           1.0f ,  0.0f, // �Ʒ� ������
           0.0f, 1.0f, // �� ����
           1.0f , 1.0f , // �� ������
    };
    texCoords[3] = {
           0.0f , 0.0f , // �Ʒ� ����
           1.0f ,  0.0f, // �Ʒ� ������
           0.0f, 1.0f, // �� ����
           1.0f , 1.0f , // �� ������
    };
    texCoords[4] = {
           0.0f , 0.0f , // �Ʒ� ����
           1.0f ,  0.0f, // �Ʒ� ������
           0.0f, 1.0f, // �� ����
           1.0f , 1.0f , // �� ������
    };
    texCoords[5] = {
           0.0f , 0.0f , // �Ʒ� ����
           1.0f ,  0.0f, // �Ʒ� ������
           0.0f, 1.0f, // �� ����
           1.0f , 1.0f , // �� ������
    };

}

void Box::draw(GLuint shaderProgramID, GLuint vbo[], GLuint textureID[]) {
    glUseProgram(shaderProgramID);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureID[1]);
    setSelectedTexture(shaderProgramID, 1);
    glUniform1i(glGetUniformLocation(shaderProgramID, "Texture1"), 1);
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
glm::mat4 Box::createTransformMatrix() {
    glm::mat4 Tx = glm::translate(glm::mat4(1.0f), glm::vec3(moving_Box_X, moving_Box_Y, moving_Box_Z));
    glm::mat4 Ty_1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.6f, 0.0f));
    glm::mat4 Ty_2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.6f, 0.0f));
    glm::mat4 Ry = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngleY), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Rx = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngleX), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 Rz = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngleZ), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 TR = Tx * Ty_1 * Ry * Rx * Rz * Ty_2;
    return TR;
}