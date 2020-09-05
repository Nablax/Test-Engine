#version 330 core
out vec4 FragColor

in vec3 TexCoords;

uniform sample2D quadTexture;

void main(){
    FragColor = texture(quadTexture, TexCoords);
}