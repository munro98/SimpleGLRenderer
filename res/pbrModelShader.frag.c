#version 330 core
in vec2 TexCoord;
in vec3 surfaceNormal;

in vec3 toLightVector;

out vec4 color;

uniform vec3 lightColour;
uniform sampler2D ourTexture1;
//uniform vec3 light_direction;
//const vec3 light_direction = vec3(-0.5, 0.6, 0.7);
void main()
{
	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitLightVector = normalize(toLightVector);

	float nDotl = dot(unitNormal, unitLightVector);
	float brightness = max(nDotl, 0.1);
	vec3 diffuse = brightness * lightColour;

	vec4 texdiffuse = texture(ourTexture1, TexCoord);
	//vec4 finalColour = vec4(0, 0, 0, 0);
	//finalColour += texdiffuse * diff;
	//finalColour += texdiffuse * 0.1;

	color = vec4(diffuse, 1.0) * texdiffuse;
	//color = finalColour;

	//color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}