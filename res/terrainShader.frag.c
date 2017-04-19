#version 330 core
in vec2 TexCoords;
in vec3 Normal;
in vec3 WorldPos;

out vec4 color;


uniform sampler2D ourTexture1;
//uniform vec3 light_direction;
//const vec3 light_direction = vec3(-0.5, 0.6, 0.7);
uniform vec3 lightPosition;
uniform vec3 lightColour;


uniform vec3 camPos;

void main()
{

	color = texture(ourTexture1, TexCoords);
	//color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}