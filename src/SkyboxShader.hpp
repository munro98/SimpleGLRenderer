#pragma once
#include "Shader.hpp"

class SkyboxShader :
	public Shader
{
public:
	SkyboxShader(std::string name);
	~SkyboxShader();
	void getAllUniformLocations();
	void loadViewMatrix(glm::mat4 mat);
	void loadProjectionMatrix(glm::mat4 mat);
private:
	GLuint mlocation_view;
	GLuint mlocation_projection;
};

