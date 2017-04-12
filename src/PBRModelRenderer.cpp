#include "PBRModelRenderer.hpp"

#include "OBJLoader.hpp"
#include "Texture.hpp"
#include "Loader.hpp"



PBRModelRenderer::PBRModelRenderer(glm::mat4 projectionMatrix) : m_shader(PBRModelShader("pbrModelShader"))
{
	m_shader.use();
	m_shader.loadProjectionMatrix(projectionMatrix);
	m_shader.loadLightPosition(glm::vec3(1000, 1500, -1000));
	m_shader.loadLightColour(glm::vec3(2.0, 2.0, 2.0));
	m_shader.stop();

	m_mesh = OBJLoader::loadObjModel("box");
	m_texture = Loader::loadTexture("ground2048");
}

PBRModelRenderer::~PBRModelRenderer()
{
}


void PBRModelRenderer::render(glm::mat4 view, glm::mat4 model, glm::mat4 projection)
{
	m_shader.use();
	//Update uniforms
	m_shader.loadModelMatrix(model);
	m_shader.loadViewMatrix(view);
	m_shader.loadProjectionMatrix(projection);

	glBindVertexArray(m_mesh->getVaoID());


	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//Bind texture
	glActiveTexture(GL_TEXTURE0);
	m_texture->bind();

	glDrawElements(GL_TRIANGLES, m_mesh->getVertexCount(), GL_UNSIGNED_INT, 0);
	Texture::unbind();

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	//*/
	glBindVertexArray(0);


}