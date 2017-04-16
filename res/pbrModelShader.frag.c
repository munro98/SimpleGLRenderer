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

uniform float metallic;
uniform float roughness;
uniform float ao;

uniform vec3 camPos;

const float PI = 3.14159265359;


float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness*roughness;
    float a2 = a*a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}
// ----------------------------------------------------------------------------
vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

void main()
{
	vec3 albedo = texture(ourTexture1, TexCoords).xyz;


	vec3 N = normalize(Normal);
	vec3 V = normalize(camPos - WorldPos);

	vec3 F0 = vec3(0.01);
	F0 = mix(F0, albedo, metallic);

	vec3 Lo = vec3(0.0);


	////////////////////////////////////////////////////////////
	// light radiance
	// calculate per-light radiance
        vec3 L = normalize(lightPosition - WorldPos);
        vec3 H = normalize(V + L);
        float distance = length(lightPosition - WorldPos);
        float attenuation = 1.0 / (distance * distance);
        vec3 radiance = lightColour * attenuation;

        // Cook-Torrance BRDF
        float NDF = DistributionGGX(N, H, roughness);   
        float G   = GeometrySmith(N, V, L, roughness);      
        vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);
           
        vec3 nominator    = NDF * G * F; 
        float denominator = 1 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.001; // 0.001 to prevent divide by zero.
        vec3 brdf = nominator / denominator;
        
        // kS is equal to Fresnel
        vec3 kS = F;
        // for energy conservation, the diffuse and specular light can't
        // be above 1.0 (unless the surface emits light); to preserve this
        // relationship the diffuse component (kD) should equal 1.0 - kS.
        vec3 kD = vec3(1.0) - kS;
        // multiply kD by the inverse metalness such that only non-metals 
        // have diffuse lighting, or a linear blend if partly metal (pure metals
        // have no diffuse light).
        kD *= 1.0 - metallic;	  

        // scale light by NdotL
        float NdotL = max(dot(N, L), 0.0);        

        // add to outgoing radiance Lo
        Lo += (kD * albedo / PI + brdf) * radiance * NdotL;  // note that we already multiplied the BRDF by the Fresnel (kS) so we won't multiply by kS again
	///////////////////////////////////////////////////////////////

	vec3 ambient = vec3(0.6) * albedo * ao;
	vec3 finalColour = ambient + Lo;

	finalColour = finalColour / (finalColour + vec3(1.0));
	finalColour = pow(finalColour, vec3(1.0/2.2));


	//float nDotl = dot(N, L);
	//float brightness = max(nDotl, 0.1);
	//vec3 diffuse = brightness * lightColour;

	
	//vec4 finalColour = vec4(0, 0, 0, 0);
	//finalColour += texdiffuse * diff;
	//finalColour += texdiffuse * 0.1;

	//color = vec4(diffuse, 1.0) * vec4(albedo, 1.0);
	color = vec4(finalColour, 1.0);

	//color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}