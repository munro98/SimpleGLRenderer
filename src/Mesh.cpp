#include "Mesh.hpp"



Mesh::Mesh(GLuint vaoID, int vertexCount) : m_vaoID(vaoID), m_vertexCount(vertexCount)
{
	
}


Mesh::~Mesh()
{
}


int Mesh::getVertexCount()
{
	return m_vertexCount;
}

GLuint Mesh::getVaoID()
{
	return m_vaoID;
}