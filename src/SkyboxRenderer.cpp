#include "SkyboxRenderer.hpp"
#include "OBJLoader.hpp"
#include "ModelShader.hpp"



SkyboxRenderer::SkyboxRenderer(glm::mat4 projectionMatrix) : m_shader(ModelShader("skyboxShader")), m_skyCubeFaces({"right", "left", "top", "bottom", "back", "front"})
{


	m_cube = OBJLoader::loadObjModel("skyCube"); // Note NORMALS FACE INWARD!
	m_cubeMapTexture = Loader::loadCubeMap(m_skyCubeFaces);

	//std::cout << m_cube->getVaoID();
	m_shader.use();
	m_shader.loadProjectionMatrix(projectionMatrix);
	m_shader.stop();
}


SkyboxRenderer::~SkyboxRenderer()
{
}

void SkyboxRenderer::render(glm::mat4 view, glm::mat4 model)
{

	m_shader.use();
	//m_shader.loadViewMatrix(viewMatrix);
	view[3][0] = 0.0f;
	view[3][1] = 0.0f;
	view[3][2] = 0.0f;
	m_shader.loadModelMatrix(model);
	m_shader.loadViewMatrix(view);

	glBindVertexArray(m_cube->getVaoID());
	//glBindVertexArray(VAO);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//load texture
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, texture);
	//texture2->bind();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubeMapTexture);

	glDrawElements(GL_TRIANGLES, m_cube->getVertexCount(), GL_UNSIGNED_INT, 0);
	//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	//*/
	glBindVertexArray(0);
	m_shader.stop();
}