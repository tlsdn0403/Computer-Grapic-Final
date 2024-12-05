#include"FenceShape.h"
FenceShape::FenceShape() {
    faces.resize(12); // Allocate space for 12 faces
    vertexColors.resize(12);
    rotationAngleY = 0.0f;
    rotationAngleX = 0.0f;
    rotationAngleZ = 0.0f;
    moving_fence_X = 1.0f;
    moving_fence_Y = .0f;
    moving_fence_Z = 0.0f;
    size = 0.05f; // Default size
    width = 0.3f;
    position = glm::vec3(0.0f);
    color = glm::vec3(1.0f); // Default white color
}

void FenceShape::generateFaces() {
    float heightMultiplier = 15.0f; // Makes the leg longer along the y-axis

    // Define faces and vertex colors here as in the original code
    // Example for the front face:
    // Front Face (Z+)
    faces[0] = {
       position[0] -width - size - size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-left 
       position[0] -width + size - size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-right 
       position[0] -width - size - size, position[1], position[2] + size,  // Top-left 
       position[0] -width + size - size, position[1], position[2] + size   // Top-right
    };
    vertexColors[0] = {
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2]
    };

    // Right Face (X+)
    faces[1] = {
       position[0] -width + size - size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-left 
       position[0] -width + size - size, position[1] - size * heightMultiplier, position[2] - size,  // Bottom-right 
       position[0] -width + size - size, position[1], position[2] + size,  // Top-left 
       position[0] -width + size - size, position[1], position[2] - size   // Top-right
    };
    vertexColors[1] = {
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2]
    };

    // Back Face (Z-)
    faces[2] = {
       position[0] -width - size - size, position[1] - size * heightMultiplier, position[2] - size,  // Bottom-left 
       position[0] -width + size - size, position[1] - size * heightMultiplier, position[2] - size,  // Bottom-right 
       position[0] -width - size - size, position[1], position[2] - size,  // Top-left 
       position[0] -width + size - size, position[1], position[2] - size   // Top-right
    };
    vertexColors[2] = {
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2]
    };

    // Left Face (X-)
    faces[3] = {
       position[0] -width - size - size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-left 
       position[0] -width - size - size, position[1] - size * heightMultiplier, position[2] - size,  // Bottom-right 
       position[0] -width - size - size, position[1], position[2] + size,  // Top-left 
       position[0] -width - size - size, position[1], position[2] - size   // Top-right
    };
    vertexColors[3] = {
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2]
    };

    // Top Face (Y+)
    faces[4] = {
       position[0] -width - size - size, position[1], position[2] + size,  // Bottom-left 
       position[0] -width + size - size, position[1], position[2] + size,  // Bottom-right 
       position[0] -width - size - size, position[1], position[2] - size,  // Top-left 
       position[0] -width + size - size, position[1], position[2] - size   // Top-right
    };
    vertexColors[4] = {
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2]
    };

    // Bottom Face (Y-)
    faces[5] = {
       position[0] -width - size - size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-left 
       position[0] -width + size - size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-right 
       position[0] -width - size - size, position[1] - size * heightMultiplier, position[2] - size,  // Top-left 
       position[0] -width + size - size, position[1] - size * heightMultiplier, position[2] - size   // Top-right
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
        position[0]  +width - size + size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-left
       position[0] +width + size + size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-right
       position[0] +width - size + size, position[1], position[2] + size,  // Top-left
       position[0] +width + size + size, position[1], position[2] + size   // Top-right
    };
    vertexColors[6] = {
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2]
    };

    // Right Face (X+)
    faces[7] = {
       position[0] +width + size + size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-left
       position[0] +width + size + size, position[1] - size * heightMultiplier, position[2] - size,  // Bottom-right
       position[0] +width + size + size, position[1], position[2] + size,  // Top-left
       position[0] +width + size + size, position[1], position[2] - size   // Top-right
    };
    vertexColors[7] = {
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2]
    };

    // Back Face (Z-)
    faces[8] = {
       position[0] +width - size + size, position[1] - size * heightMultiplier, position[2] - size,  // Bottom-left
       position[0] +width + size + size, position[1] - size * heightMultiplier, position[2] - size,  // Bottom-right
       position[0] +width - size + size, position[1], position[2] - size,  // Top-left
       position[0] +width + size + size, position[1], position[2] - size   // Top-right
    };
    vertexColors[8] = {
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2]
    };

    // Left Face (X-)
    faces[9] = {
       position[0] +width - size + size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-left
       position[0] +width - size + size, position[1] - size * heightMultiplier, position[2] - size,  // Bottom-right
       position[0] +width - size + size, position[1], position[2] + size,  // Top-left
       position[0] +width - size + size, position[1], position[2] - size   // Top-right
    };
    vertexColors[9] = {
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2]
    };

    // Top Face (Y+)
    faces[10] = {
       position[0] +width - size + size, position[1], position[2] + size,  // Bottom-left
       position[0] +width + size + size, position[1], position[2] + size,  // Bottom-right
       position[0] +width - size + size, position[1], position[2] - size,  // Top-left
       position[0] +width + size + size, position[1], position[2] - size   // Top-right
    };
    vertexColors[10] = {
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2]
    };

    // Bottom Face (Y-)
    faces[11] = {
       position[0] +width - size + size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-left
       position[0] +width + size + size, position[1] - size * heightMultiplier, position[2] + size,  // Bottom-right
       position[0] +width - size + size, position[1] - size * heightMultiplier, position[2] - size,  // Top-left
       position[0] +width + size + size, position[1] - size * heightMultiplier, position[2] - size   // Top-right
    };
    vertexColors[11] = {
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2],
        color[0], color[1], color[2]
    };

   


}

void FenceShape::draw(GLuint shaderProgramID, GLuint vbo[]) {
    for (int i = 0; i < 12; i++) {
        if (i >= faces.size()) {
            std::cerr << "Error: faces vector index out of range." << std::endl;
            continue;
        }
        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, faces[i].size() * sizeof(GLfloat), faces[i].data());
        glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertexColors[i].size() * sizeof(GLfloat), vertexColors[i].data());


        glm::mat4 modelMatrix = createTransformMatrix();

        GLuint mvpLocation = glGetUniformLocation(shaderProgramID, "uMVP");
        glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); // Adjust based on your drawing mode
    }
}

glm::mat4 FenceShape::createTransformMatrix() {
    glm::mat4 Tx = glm::translate(glm::mat4(1.0f), glm::vec3(moving_fence_X, moving_fence_Y, moving_fence_Z));
    glm::mat4 Ty_1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.6f, 0.0f));
    glm::mat4 Ty_2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.6f, 0.0f));
    glm::mat4 Ry = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngleY), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Rx = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngleX), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 Rz = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngleZ), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 TR = Tx * Ty_1 * Ry * Rx * Rz * Ty_2;
    return TR;
}