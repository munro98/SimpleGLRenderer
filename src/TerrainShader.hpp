#pragma once

#include "Shader.hpp"
#include "OBJLoader.hpp"
#include "Texture.hpp"
#include "Loader.hpp"

class TerrainShader : public Shader
{
public:
	TerrainShader(std::string name);
	~TerrainShader();

	void bindAttributes();

	void getAllUniformLocations();

	void loadModelMatrix(glm::mat4 mat);

	void loadViewMatrix(glm::mat4 mat);

	void loadProjectionMatrix(glm::mat4 mat);

	void loadLightPosition(glm::vec3 lightColour);

	void loadLightColour(glm::vec3 lightColour);

	void loadCamPos(glm::vec3 camPos);


private:
	GLuint m_location_model;
	GLuint m_location_view;
	GLuint m_location_projection;

	GLuint m_location_lightPosition;
	GLuint m_location_lightColour;

	GLuint m_location_camPos;
};

