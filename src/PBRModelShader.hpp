#pragma once

#include "Shader.hpp"
#include "OBJLoader.hpp"
#include "Texture.hpp"
#include "Loader.hpp"

class PBRModelShader : public Shader
{
public:
	PBRModelShader(std::string name);
	~PBRModelShader();

	void bindAttributes();

	void getAllUniformLocations();

	void loadModelMatrix(glm::mat4 mat);

	void loadViewMatrix(glm::mat4 mat);

	void loadProjectionMatrix(glm::mat4 mat);

	void loadLightPosition(glm::vec3 lightColour);

	void loadLightColour(glm::vec3 lightColour);

	void loadCamPos(glm::vec3 camPos);

	void loadMetallic(float value);

	void loadRoughness(float value);

	void loadAO(float value);

private:
	GLuint m_location_model;
	GLuint m_location_view;
	GLuint m_location_projection;

	GLuint m_location_lightPosition;
	GLuint m_location_lightColour;

	GLuint m_location_metallic;
	GLuint m_location_roughness;
	GLuint m_location_ao;

	GLuint m_location_camPos;
};

