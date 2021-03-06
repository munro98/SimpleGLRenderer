#include "PBRModelShader.hpp"



PBRModelShader::PBRModelShader(std::string name) : Shader(name)
{
	getAllUniformLocations();
}


PBRModelShader::~PBRModelShader()
{
}

void PBRModelShader::bindAttributes()
{
	Shader::bindAttribute(0, "position");
	Shader::bindAttribute(1, "textureCoords");
	Shader::bindAttribute(2, "normal");
}

void PBRModelShader::getAllUniformLocations()
{
	m_location_model = Shader::getUniformLocation("model");
	m_location_view = Shader::getUniformLocation("view");
	m_location_projection = Shader::getUniformLocation("projection");

	m_location_lightPosition = Shader::getUniformLocation("lightPosition");
	m_location_lightColour = Shader::getUniformLocation("lightColour");

	m_location_metallic = Shader::getUniformLocation("metallic");
	m_location_roughness = Shader::getUniformLocation("roughness");
	m_location_ao = Shader::getUniformLocation("ao");

	m_location_camPos = Shader::getUniformLocation("camPos");
	//assert(m_location_lightPosition != 0);
	//assert(m_location_lightColour != 0);
}


void PBRModelShader::loadModelMatrix(glm::mat4 mat)
{
	Shader::loadMatrix(m_location_model, mat);
}

void PBRModelShader::loadViewMatrix(glm::mat4 mat)
{
	Shader::loadMatrix(m_location_view, mat);
}

void PBRModelShader::loadProjectionMatrix(glm::mat4 mat)
{
	Shader::loadMatrix(m_location_projection, mat);
}

void PBRModelShader::loadLightPosition(glm::vec3 lightColour)
{
	Shader::loadVector(m_location_lightPosition, lightColour);
}

void PBRModelShader::loadLightColour(glm::vec3 lightColour)
{
	Shader::loadVector(m_location_lightColour, lightColour);
}

void PBRModelShader::loadCamPos(glm::vec3 camPos)
{
	Shader::loadVector(m_location_camPos, camPos);
}

void PBRModelShader::loadMetallic(float value)
{
	Shader::loadFloat(m_location_metallic, value);
}

void PBRModelShader::loadRoughness(float value)
{
	Shader::loadFloat(m_location_roughness, value);
}

void PBRModelShader::loadAO(float value)
{
	Shader::loadFloat(m_location_ao, value);
}