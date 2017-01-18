#version 330 core
in vec3 position;
in vec2 texcoord;
in vec3 normal;

out vec2 TexCoords;
out vec3 WorldPos;
out vec3 Normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    TexCoords = texcoord;
    WorldPos = vec3(model * vec4(position, 1.0f));
    Normal = mat3(model) * normal;
    
    gl_Position =  projection * view * vec4(WorldPos, 1.0);
}
