#version 330 core  

// Input from the vertex shader
in vec3 ourColor;
in vec2 TexCoord;  

// Uniforms
uniform sampler2D Textures[];
uniform sampler2D Texture0;  
uniform int selectedTexture; // ������� �ؽ�ó�� ����� ������

// Output color
out vec4 FragColor;

void main() {  
    if (selectedTexture == 0) {
        // �ؽ�ó�� ����ϴ� ���
        FragColor = texture(Texture0, TexCoord);
    } else {
        // �ؽ�ó�� ������� �ʴ� ��� �⺻ ����
        FragColor = vec4(ourColor, 1.0);
    }
}
