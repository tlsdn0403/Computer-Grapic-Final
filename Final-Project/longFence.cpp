#include"longFence.h"



longFence::longFence() {
    faces.resize(22); // Allocate space for 12 faces
    vertexColors.resize(22);
    texCoords.resize(22);

    size = 0.08f; // Default size
    width = 0.3f;  //두 울타리 다리의 너비
    position = glm::vec3(0.0f);
    color = glm::vec3(1.0f); // Default white color
}

void longFence::generateFaces() {
    float heightMultiplier = 20.0f; // 울타리 높이


    // Front Face (Z+)
    faces[0] = {
       position[0] - width - size - size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-left 
       position[0] - width + size - size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-right 
       position[0] - width - size - size, position[1], position[2] + size,  // Top-left 
       position[0] - width + size - size, position[1], position[2] + size   // Top-right
    };
    vertexColors[0] = {
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2]
    };

    // Right Face (X+)
    faces[1] = {
       position[0] - width + size - size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-left 
       position[0] - width + size - size, position[1] - size * heightMultiplier, position[2] - size,  // Bottom-right 
       position[0] - width + size - size, position[1], position[2] + size,  // Top-left 
       position[0] - width + size - size, position[1], position[2] - size   // Top-right
    };
    vertexColors[1] = {
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2]
    };

    // Back Face (Z-)
    faces[2] = {
       position[0] - width - size - size, position[1] - size * heightMultiplier, position[2] - size,  // Bottom-left 
       position[0] - width + size - size, position[1] - size * heightMultiplier, position[2] - size,  // Bottom-right 
       position[0] - width - size - size, position[1], position[2] - size,  // Top-left 
       position[0] - width + size - size, position[1], position[2] - size   // Top-right
    };
    vertexColors[2] = {
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2]
    };

    // Left Face (X-)
    faces[3] = {
       position[0] - width - size - size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-left 
       position[0] - width - size - size, position[1] - size * heightMultiplier, position[2] - size,  // Bottom-right 
       position[0] - width - size - size, position[1], position[2] + size,  // Top-left 
       position[0] - width - size - size, position[1], position[2] - size   // Top-right
    };
    vertexColors[3] = {
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2]
    };

    // Top Face (Y+)
    faces[4] = {
       position[0] - width - size - size, position[1], position[2] + size,  // Bottom-left 
       position[0] - width + size - size, position[1], position[2] + size,  // Bottom-right 
       position[0] - width - size - size, position[1], position[2] - size,  // Top-left 
       position[0] - width + size - size, position[1], position[2] - size   // Top-right
    };
    vertexColors[4] = {
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2]
    };

    // Bottom Face (Y-)
    faces[5] = {
       position[0] - width - size - size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-left 
       position[0] - width + size - size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-right 
       position[0] - width - size - size, position[1] - size * heightMultiplier, position[2] - size,  // Top-left 
       position[0] - width + size - size, position[1] - size * heightMultiplier, position[2] - size   // Top-right
    };
    vertexColors[5] = {
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2]
    };
    // 울타리 오른쪽 다리

    // Front Face (Z+)
    faces[6] = {
        position[0] + width , position[1] - size * heightMultiplier, position[2] + size,  // Bottom-left
       position[0] + width + size + size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-right
       position[0] + width , position[1], position[2] + size,  // Top-left
       position[0] + width + size + size, position[1], position[2] + size   // Top-right
    };
    vertexColors[6] = {
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2]
    };

    // Right Face (X+)
    faces[7] = {
       position[0] + width + size + size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-left
       position[0] + width + size + size, position[1] - size * heightMultiplier, position[2] - size,  // Bottom-right
       position[0] + width + size + size, position[1], position[2] + size,  // Top-left
       position[0] + width + size + size, position[1], position[2] - size   // Top-right
    };
    vertexColors[7] = {
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2]
    };

    // Back Face (Z-)
    faces[8] = {
       position[0] + width - size + size, position[1] - size * heightMultiplier, position[2] - size,  // Bottom-left
       position[0] + width + size + size, position[1] - size * heightMultiplier, position[2] - size,  // Bottom-right
       position[0] + width - size + size, position[1], position[2] - size,  // Top-left
       position[0] + width + size + size, position[1], position[2] - size   // Top-right
    };
    vertexColors[8] = {
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2]
    };

    // Left Face (X-)
    faces[9] = {
       position[0] + width - size + size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-left
       position[0] + width - size + size, position[1] - size * heightMultiplier, position[2] - size,  // Bottom-right
       position[0] + width - size + size, position[1], position[2] + size,  // Top-left
       position[0] + width - size + size, position[1], position[2] - size   // Top-right
    };
    vertexColors[9] = {
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2]
    };

    // Top Face (Y+)
    faces[10] = {
       position[0] + width - size + size, position[1], position[2] + size,  // Bottom-left
       position[0] + width + size + size, position[1], position[2] + size,  // Bottom-right
       position[0] + width - size + size, position[1], position[2] - size,  // Top-left
       position[0] + width + size + size, position[1], position[2] - size   // Top-right
    };
    vertexColors[10] = {
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2]
    };

    // Bottom Face (Y-)
    faces[11] = {
       position[0] + width - size + size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-left
       position[0] + width + size + size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-right
       position[0] + width - size + size, position[1] - size * heightMultiplier, position[2] - size,  // Top-left
       position[0] + width + size + size, position[1] - size * heightMultiplier, position[2] - size   // Top-right
    };
    vertexColors[11] = {
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2]
    };


    //맨 위에 있는 가로 사각형
    //Z+
    faces[12] = {
       position[0] - (width * 2 + size + size), position[1] - size , position[2] + size,  // Bottom-left
       position[0] + width * 2 + size + size, position[1] - size , position[2] + size,  // Bottom-right
       position[0] - (width * 2 + size + size), position[1] - 2 * size   , position[2] + size,  // Top-left
       position[0] + width * 2 + size + size, position[1] - 2 * size  , position[2] + size   // Top-right
    };
    //오른쪽 면
    faces[13] = {
       position[0] + (width * 2 + size + size), position[1] - size , position[2] + size,  // Bottom-left
       position[0] + width * 2 + size + size, position[1] - size , position[2] - size,  // Bottom-right
       position[0] + (width * 2 + size + size), position[1] - 2 * size, position[2] + size,  // Top-left
       position[0] + width * 2 + size + size, position[1] - 2 * size, position[2] - size   // Top-right
    };

    //왼쪽 면
    faces[14] = {
       position[0] - (width * 2 + size + size), position[1] - size , position[2] + size,  // Bottom-left
       position[0] - (width * 2 + size + size), position[1] - size , position[2] - size,  // Bottom-right
       position[0] - (width * 2 + size + size), position[1] - 2 * size, position[2] + size,  // Top-left
       position[0] - (width * 2 + size + size), position[1] - 2 * size, position[2] - size   // Top-right
    };
    //Z-
    faces[15] = {
       position[0] - (width * 2 + size + size), position[1] - size , position[2] - size,  // Bottom-left
       position[0] + width * 2 + size + size, position[1] - size , position[2] - size,  // Bottom-right
       position[0] - (width * 2 + size + size), position[1] - 2 * size, position[2] - size,  // Top-left
       position[0] + width * 2 + size + size, position[1] - 2 * size, position[2] - size   // Top-right
    };
    //Y-
    faces[16] = {
       position[0] - (width * 2 + size + size), position[1] - size   , position[2] + size,  // Bottom-left
       position[0] + width * 2 + size + size, position[1] - size  , position[2] + size,  // Bottom-right
       position[0] - (width * 2 + size + size), position[1] - 2 * size , position[2] - size,  // Top-left
       position[0] + width * 2 + size + size, position[1] - 2 * size , position[2] - size   // Top-right
    };


    //맨 위에 있는 가로 사각형
    //Z+
    faces[17] = {
       position[0] - (width * 2 + size + size), position[1] - 3 * size - size , position[2] + size,  // Bottom-left
       position[0] + width * 2 + size + size, position[1] - 3 * size - size , position[2] + size,  // Bottom-right
       position[0] - (width * 2 + size + size), position[1] - 3 * size - 2 * size   , position[2] + size,  // Top-left
       position[0] + width * 2 + size + size, position[1] - 3 * size - 2 * size  , position[2] + size   // Top-right
    };
    //오른쪽 면
    faces[18] = {
       position[0] + (width * 2 + size + size), position[1] - 3 * size - size , position[2] + size,  // Bottom-left
       position[0] + width * 2 + size + size, position[1] - 3 * size - size , position[2] - size,  // Bottom-right
       position[0] + (width * 2 + size + size), position[1] - 3 * size - 2 * size, position[2] + size,  // Top-left
       position[0] + width * 2 + size + size, position[1] - 3 * size - 2 * size, position[2] - size   // Top-right
    };

    //왼쪽 면
    faces[19] = {
       position[0] - (width * 2 + size + size), position[1] - 3 * size - size , position[2] + size,  // Bottom-left
       position[0] - (width * 2 + size + size), position[1] - 3 * size - size , position[2] - size,  // Bottom-right
       position[0] - (width * 2 + size + size), position[1] - 3 * size - 2 * size, position[2] + size,  // Top-left
       position[0] - (width * 2 + size + size), position[1] - 3 * size - 2 * size, position[2] - size   // Top-right
    };
    //Z-
    faces[20] = {
       position[0] - (width * 2 + size + size), position[1] - 3 * size - size , position[2] - size,  // Bottom-left
       position[0] + width * 2 + size + size, position[1] - 3 * size - size , position[2] - size,  // Bottom-right
       position[0] - (width * 2 + size + size), position[1] - 3 * size - 2 * size, position[2] - size,  // Top-left
       position[0] + width * 2 + size + size, position[1] - 3 * size - 2 * size, position[2] - size   // Top-right
    };
    //Y-
    faces[21] = {
       position[0] - (width * 2 + size + size), position[1] - 3 * size - size   , position[2] + size,  // Bottom-left
       position[0] + width * 2 + size + size, position[1] - 3 * size - size  , position[2] + size,  // Bottom-right
       position[0] - (width * 2 + size + size), position[1] - 3 * size - 2 * size , position[2] - size,  // Top-left
       position[0] + width * 2 + size + size, position[1] - 3 * size - 2 * size , position[2] - size   // Top-right
    };


    // 텍스처 좌표
    texCoords[0] = {
           0.0f , 0.0f , // 아래 왼쪽
           1.0f ,  0.0f, // 아래 오른쪽
           0.0f, 1.0f, // 위 왼쪽
           1.0f , 1.0f , // 위 오른쪽
    };
    texCoords[1] = {
           0.0f , 0.0f , // 아래 왼쪽
           1.0f ,  0.0f, // 아래 오른쪽
           0.0f, 1.0f, // 위 왼쪽
           1.0f , 1.0f , // 위 오른쪽
    };
    texCoords[2] = {
           0.0f , 0.0f , // 아래 왼쪽
           1.0f ,  0.0f, // 아래 오른쪽
           0.0f, 1.0f, // 위 왼쪽
           1.0f , 1.0f , // 위 오른쪽
    };
    texCoords[3] = {
           0.0f , 0.0f , // 아래 왼쪽
           1.0f ,  0.0f, // 아래 오른쪽
           0.0f, 1.0f, // 위 왼쪽
           1.0f , 1.0f , // 위 오른쪽
    };
    texCoords[4] = {
           0.0f , 0.0f , // 아래 왼쪽
           1.0f ,  0.0f, // 아래 오른쪽
           0.0f, 1.0f, // 위 왼쪽
           1.0f , 1.0f , // 위 오른쪽
    };
    texCoords[5] = {
           0.0f , 0.0f , // 아래 왼쪽
           1.0f ,  0.0f, // 아래 오른쪽
           0.0f, 1.0f, // 위 왼쪽
           1.0f , 1.0f , // 위 오른쪽
    };
    texCoords[6] = {
           0.0f , 0.0f , // 아래 왼쪽
           1.0f ,  0.0f, // 아래 오른쪽
           0.0f, 1.0f, // 위 왼쪽
           1.0f , 1.0f , // 위 오른쪽
    };
    texCoords[7] = {
           0.0f , 0.0f , // 아래 왼쪽
           1.0f ,  0.0f, // 아래 오른쪽
           0.0f, 1.0f, // 위 왼쪽
           1.0f , 1.0f , // 위 오른쪽
    };
    texCoords[8] = {
           0.0f , 0.0f , // 아래 왼쪽
           1.0f ,  0.0f, // 아래 오른쪽
           0.0f, 1.0f, // 위 왼쪽
           1.0f , 1.0f , // 위 오른쪽
    };
    texCoords[9] = {
           0.0f , 0.0f , // 아래 왼쪽
           1.0f ,  0.0f, // 아래 오른쪽
           0.0f, 1.0f, // 위 왼쪽
           1.0f , 1.0f , // 위 오른쪽
    };
    texCoords[10] = {
           0.0f , 0.0f , // 아래 왼쪽
           1.0f ,  0.0f, // 아래 오른쪽
           0.0f, 1.0f, // 위 왼쪽
           1.0f , 1.0f , // 위 오른쪽
    };
    texCoords[11] = {
          0.0f , 0.0f , // 아래 왼쪽
           1.0f ,  0.0f, // 아래 오른쪽
           0.0f, 1.0f, // 위 왼쪽
           1.0f , 1.0f , // 위 오른쪽
    };
    texCoords[12] = {
           0.0f , 0.0f , // 아래 왼쪽
            1.0f ,  0.0f, // 아래 오른쪽
            0.0f, 1.0f, // 위 왼쪽
            1.0f , 1.0f , // 위 오른쪽
    };
    texCoords[13] = {
           0.0f , 0.0f , // 아래 왼쪽
            1.0f ,  0.0f, // 아래 오른쪽
            0.0f, 1.0f, // 위 왼쪽
            1.0f , 1.0f , // 위 오른쪽
    };
    texCoords[14] = {
           0.0f , 0.0f , // 아래 왼쪽
            1.0f ,  0.0f, // 아래 오른쪽
            0.0f, 1.0f, // 위 왼쪽
            1.0f , 1.0f , // 위 오른쪽
    };
    texCoords[15] = {
           0.0f , 0.0f , // 아래 왼쪽
            1.0f ,  0.0f, // 아래 오른쪽
            0.0f, 1.0f, // 위 왼쪽
            1.0f , 1.0f , // 위 오른쪽
    };
    texCoords[16] = {
           0.0f , 0.0f , // 아래 왼쪽
            1.0f ,  0.0f, // 아래 오른쪽
            0.0f, 1.0f, // 위 왼쪽
            1.0f , 1.0f , // 위 오른쪽
    };
    texCoords[17] = {
           0.0f , 0.0f , // 아래 왼쪽
            1.0f ,  0.0f, // 아래 오른쪽
            0.0f, 1.0f, // 위 왼쪽
            1.0f , 1.0f , // 위 오른쪽
    };
    texCoords[18] = {
           0.0f , 0.0f , // 아래 왼쪽
            1.0f ,  0.0f, // 아래 오른쪽
            0.0f, 1.0f, // 위 왼쪽
            1.0f , 1.0f , // 위 오른쪽
    };
    texCoords[19] = {
           0.0f , 0.0f , // 아래 왼쪽
            1.0f ,  0.0f, // 아래 오른쪽
            0.0f, 1.0f, // 위 왼쪽
            1.0f , 1.0f , // 위 오른쪽
    };
    texCoords[20] = {
           0.0f , 0.0f , // 아래 왼쪽
            1.0f ,  0.0f, // 아래 오른쪽
            0.0f, 1.0f, // 위 왼쪽
            1.0f , 1.0f , // 위 오른쪽
    };
    texCoords[21] = {
           0.0f , 0.0f , // 아래 왼쪽
            1.0f ,  0.0f, // 아래 오른쪽
            0.0f, 1.0f, // 위 왼쪽
            1.0f , 1.0f , // 위 오른쪽
    };
}

void longFence::draw(GLuint shaderProgramID, GLuint vbo[], GLuint textureID[]) {
    glUseProgram(shaderProgramID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID[0]);
    setSelectedTexture(shaderProgramID, 0);
    glUniform1i(glGetUniformLocation(shaderProgramID, "Texture0"), 0);
    glUniform1i(glGetUniformLocation(shaderProgramID, "selectedTexture"), 0);
    for (int i = 0; i < 21; i++) {
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

glm::mat4 longFence::createTransformMatrix() {
    glm::mat4 Tx = glm::translate(glm::mat4(1.0f), glm::vec3(moving_fence_X, moving_fence_Y, moving_fence_Z));
    glm::mat4 Ty_1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.6f, 0.0f));
    glm::mat4 Ty_2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.6f, 0.0f));
    glm::mat4 Ry = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngleY), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Rx = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngleX), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 Rz = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngleZ), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 TR = Tx * Ty_1 * Ry * Rx * Rz * Ty_2;
    return TR;
}