#version 330 core

in vec2 TexCoord;
in vec3 surfaceNormal;

in vec3 Position;

out vec4 color;

uniform sampler2D ourTexture1;

const vec3 fogColour = vec3(1,0,0);
const float lowerLimit = -600.0;
const float upperLimit = 400.0;

void main()
{

	float factor = (Position.y- lowerLimit) / (upperLimit - lowerLimit);
    factor = clamp(factor, 0.0, 1.0);
	
	color = mix(vec4(0.72, 0.83, 0.98, 1), vec4(0.35, 0.474, 0.638, 1), factor);
}