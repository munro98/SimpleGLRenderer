#pragma once
//#define SIZE = 500.0f

#include <vector>
#include <glm/glm.hpp>

#include "Loader.hpp"
#include "SkyboxShader.hpp"
#include "ModelShader.hpp"



class SkyboxRenderer
{
public:
	SkyboxRenderer(glm::mat4 projectionMatrix);
	~SkyboxRenderer();
	void render(glm::mat4 viewMatrix, glm::mat4 model);

private:

	std::vector<std::string> m_skyCubeFaces;

	static std::vector<float> m_vertices;
	Mesh *m_cube;
	ModelShader m_shader;

	
};

