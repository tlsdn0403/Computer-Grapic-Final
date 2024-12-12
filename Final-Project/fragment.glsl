#version 330 core  

// Input from the vertex shader
in vec3 ourColor;
in vec2 TexCoord;  

// Uniforms
uniform sampler2D Textures[];
uniform sampler2D Texture0;  
uniform int selectedTexture; // 몇번쨰의 텍스처를 사용할 것인지

// Output color
out vec4 FragColor;

void main() {  
    if (selectedTexture == 0) {
        // 텍스처를 사용하는 경우
        FragColor = texture(Texture0, TexCoord);
    } else {
        // 텍스처를 사용하지 않는 경우 기본 색상
        FragColor = vec4(ourColor, 1.0);
    }
}
