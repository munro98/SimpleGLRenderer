#include "SkyboxShader.hpp"
#include <string>


SkyboxShader::SkyboxShader(std::string name) : Shader(name)
{
	getAllUniformLocations();
}


SkyboxShader::~SkyboxShader()
{
}


void SkyboxShader::getAllUniformLocations()
{
	mlocation_view = Shader::getUniformLocation("view");
	mlocation_projection = Shader::getUniformLocation("projection");
}

void SkyboxShader::loadViewMatrix(glm::mat4 mat)
{
	mat[3][0] = 0.0f;
	mat[3][1] = 0.0f;
	mat[3][2] = 0.0f;
	Shader::loadMatrix(mlocation_view, mat);
}

void SkyboxShader::loadProjectionMatrix(glm::mat4 mat)
{
	Shader::loadMatrix(mlocation_projection, mat);
}