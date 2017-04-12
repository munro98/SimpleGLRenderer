#version 330 core

//layout (location = 0) in vec3 position;
//layout (location = 1) in vec3 color;
//layout (location = 2) in vec2 texCoord;

in vec3 position;
in vec2 textureCoords;
in vec3 normal;

out vec2 TexCoord;
out vec3 surfaceNormal;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0);

	// We swap the y-axis by substracing our coordinates from 1. This is done because most images have the top y-axis inversed with OpenGL's top y-axis.
	// TexCoord = texCoord;
	TexCoord = textureCoords;

	//surfaceNormal = normal;
}