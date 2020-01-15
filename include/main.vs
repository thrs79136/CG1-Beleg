#version 450 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vTexture;

uniform mat4 ModelViewProjection;
uniform mat4 Model;
uniform mat4 NormalMatrix;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoord;

void main(){
    gl_Position = ModelViewProjection * vec4(vPosition,1.0);
    FragPos = vec3(Model * vec4(vPosition,1.0));
    Normal = vec3(NormalMatrix * vec4(vNormal,1.0));
    TexCoord = vTexture;
}