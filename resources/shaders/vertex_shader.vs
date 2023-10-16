#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

out vec4 vertexColor;

uniform mat4 view;
uniform mat4 projection;

void main()
{   
    gl_Position = projection * view * position;
    vertexColor = color;
}