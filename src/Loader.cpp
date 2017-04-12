#include "Loader.hpp"
#include "stb_image.h"


Loader::Loader()
{
}


Loader::~Loader()
{
}


Mesh* Loader::loadToVAO(std::vector<float>& positions, std::vector<float>& textureCoords, std::vector<float>& normals, std::vector<int>& indices)
{
	GLuint vaoID = createVAO();
	bindIndicesBuffer(indices);
	storeDataInAttributeList(0, 3, positions);
	storeDataInAttributeList(1, 2, textureCoords);
	storeDataInAttributeList(2, 3, normals);

	glBindVertexArray(0);

	return new Mesh(vaoID, indices.size());
}

Mesh* Loader::loadToVAO(std::vector<float>& positions, int dimensions)
{
	GLuint vaoID = createVAO();
	storeDataInAttributeList(0, dimensions, positions);

	glBindVertexArray(0);

	return new Mesh(vaoID, positions.size()/dimensions);
}

GLuint Loader::createVAO() {

	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
	return vaoID;
}

void Loader::storeDataInAttributeList(int attributeNumber, int coordinateSize, std::vector<float>& data)
{
	GLuint vboID;
	glGenBuffers(1, &vboID);

	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), data.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, false, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Loader::bindIndicesBuffer(std::vector<int>& indices)
{
	GLuint VBOID;
	glGenBuffers(1, &VBOID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

Texture* Loader::loadTexture(std::string fileName)
{
	fileName = "./res/" + fileName + ".png";
	std::cout << fileName;
	const char *textureName = fileName.c_str();
	//char *textureName = "./res/TextureMap.png";
	int x, y, bytesPerPixel;
	unsigned char* textureData = stbi_load(textureName, &x, &y, &bytesPerPixel, 3);

	//if (textureData == nullptr)
	{
		//std::cout << "Texture load fail\n";
		//return nullptr;
	}

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(textureData);

	return new Texture(x, y, textureID);

}
