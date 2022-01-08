#version 330 core
layout (location = 0) in vec3 vPos;
layout(location = 1) in vec2 vTexCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projectionView;

void main()
{
	gl_Position = projectionView * model * vec4(vPos, 1.0f);
	TexCoords = vTexCoords;
}