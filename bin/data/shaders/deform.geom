#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

const float PI = 3.1415926;

uniform float time;
uniform mat4 model;
uniform mat4 model2;
uniform mat4 model3;
uniform mat4 view;
uniform mat4 projection;

in vec2 texCoords[];
out vec2 TexCoords;

vec3 GetNormal()
{
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
    return normalize(cross(a, b));
}


vec4 explode(vec4 position, vec3 normal)
{
    float magnitude = 200.0f;
    vec3 direction = normal * ((sin(time) + 1.0f) / 2.0f) * magnitude;
    return position + vec4(direction, 0.0f);
}


void main()
{
    vec3 normal = GetNormal();
    
    gl_Position = projection * view * model * explode(gl_in[0].gl_Position, normal);
    TexCoords = texCoords[0];
    EmitVertex();
    
    gl_Position = projection * view * model2 * explode(gl_in[1].gl_Position, normal);
    TexCoords = texCoords[1];
    EmitVertex();
    
    gl_Position = projection * view * model3 * explode(gl_in[2].gl_Position, normal);
    TexCoords = texCoords[2];
    EmitVertex();
    
    EndPrimitive();
}
