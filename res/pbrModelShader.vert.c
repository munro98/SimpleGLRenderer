#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoords;
layout (location = 2) in vec3 normal;

//in vec3 position;
//in vec2 textureCoords;
//in vec3 normal;

out vec2 TexCoord;
out vec3 surfaceNormal;
out vec3 toLightVector;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightPosition;

void main()
{
	vec4 worldPosition = model * vec4(position,1.0);
	gl_Position = projection * view * worldPosition;
	surfaceNormal = normal;
	toLightVector = lightPosition - worldPosition.xyz;
	//surfaceNormal = (model * vec4(normal, 0.0)).xyz;
	//vec3 thing = normal;
	TexCoord = textureCoords;

}