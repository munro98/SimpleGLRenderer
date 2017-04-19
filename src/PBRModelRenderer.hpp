#pragma once
#include "Shader.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"
#include "PBRModelShader.hpp"

#include "Terrain.hpp"

class PBRModelRenderer
{
public:
	PBRModelRenderer(glm::mat4 projectionMatrix);
	~PBRModelRenderer();

	void render(glm::mat4 view, glm::mat4 model, glm::mat4 projection, glm::vec3 camPos);

private:
	PBRModelShader m_shader;
	Mesh* m_mesh;
	Texture* m_texture;
};

