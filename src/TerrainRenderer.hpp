#pragma once
#include "Shader.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"
#include "TerrainShader.hpp"

#include "Terrain.hpp"

class TerrainRenderer
{
public:
	TerrainRenderer(glm::mat4 projectionMatrix);
	~TerrainRenderer();

	void render(glm::mat4 view, glm::mat4 model, glm::mat4 projection, glm::vec3 camPos);

private:
	TerrainShader m_shader;
	Texture* m_texture;

	Terrain m_terrain;
};

