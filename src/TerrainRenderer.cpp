#include "TerrainRenderer.hpp"

#include "OBJLoader.hpp"
#include "Texture.hpp"
#include "Loader.hpp"



TerrainRenderer::TerrainRenderer(glm::mat4 projectionMatrix) : m_shader(TerrainShader("terrainShader")), m_terrain(Terrain())
{
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_shader.use();
	m_shader.loadProjectionMatrix(projectionMatrix);
	m_shader.loadLightPosition(glm::vec3(1.0, 1.5, -2.0));
	m_shader.loadLightColour(glm::vec3(2.0, 2.0, 2.0));

	m_shader.stop();

	m_texture = Loader::loadTexture("ground2048");

	
}

TerrainRenderer::~TerrainRenderer()
{
}


void TerrainRenderer::render(glm::mat4 view, glm::mat4 model, glm::mat4 projection, glm::vec3 camPos)
{
	m_shader.use();
	//Update uniforms
	m_shader.loadModelMatrix(model);
	m_shader.loadViewMatrix(view);
	m_shader.loadProjectionMatrix(projection);

	m_shader.loadCamPos(camPos);

	glBindVertexArray(m_terrain.getMesh()->getVaoID());

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//Bind texture
	
	glActiveTexture(GL_TEXTURE0);
	m_texture->bind();

	glDrawElements(GL_TRIANGLES, m_terrain.getMesh()->getVertexCount(), GL_UNSIGNED_INT, 0);
	Texture::unbind();

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	//*/
	glBindVertexArray(0);


}