#version 330 core  

// Input from the vertex shader
in vec3 ourColor;
in vec2 TexCoord;  

// Uniforms
uniform sampler2D Textures[];
uniform sampler2D Texture0;  
uniform sampler2D Texture1;  
uniform sampler2D Texture2;  
uniform sampler2D Texture3;  
uniform int selectedTexture; // ������� �ؽ�ó�� ����� ������

// Output color
out vec4 FragColor;

void main() {  
    if (selectedTexture == 0) {
        // �ؽ�ó�� ����ϴ� ���
        FragColor = texture(Texture0, TexCoord);
    }
    else if(selectedTexture==1){
        FragColor = texture(Texture1, TexCoord);
    }
    else if(selectedTexture==2){
        FragColor = texture(Texture2, TexCoord);
    }
     else if(selectedTexture==3){
        FragColor = texture(Texture3, TexCoord);
    }
    else {
        // �ؽ�ó�� ������� �ʴ� ��� �⺻ ����
        FragColor = vec4(ourColor, 1.0);
    }
}
