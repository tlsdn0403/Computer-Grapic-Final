#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;

uniform mat4 uMVP;              // Model matrix (or combined model-view)
uniform mat4 projectionTransform;
uniform mat4 viewTransform;

out vec3 fragColor;

void main() {
    // Correct order of transformations: projection * view * model * vertex
    gl_Position =projectionTransform *viewTransform* uMVP * vec4(inPosition, 1.0);
    fragColor = inColor;
}
