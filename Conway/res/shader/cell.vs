#version 330 core

layout (location = 0) in vec2 lPos;

out vec2 oTexPos;

uniform mat4 uModel;

void main()
{
    gl_Position = uModel * vec4(lPos, 0.0, 1.0);
	oTexPos = lPos;
}
