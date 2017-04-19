#include "Terrain.hpp"



Terrain::Terrain()
{
	m_mesh = generateTerrain2();
}


Terrain::~Terrain()
{
	delete m_mesh;
}

Mesh * Terrain::generateTerrain()
{

	float heightMap[VERTEX_COUNT][VERTEX_COUNT];
	//std::vector<float> heights();


	int count = VERTEX_COUNT * VERTEX_COUNT;

	std::vector<float> vertices = { -0.5f,-0.5f,0.0f,
		0.5f,-0.5f,0.0f,
		0.0f,0.5f,0.0f };
	std::vector<float> normals = { 0.0f,1.0f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,1.0f,0.0f };
	std::vector<float> textureCoords = { -0.5f,-0.5f,
		0.5f,-0.5f,
		0.0f,0.5f};
	std::vector<int> indices = {0, 1, 2};
	///*
	vertices.resize(count * 3);
	normals.resize(count * 3);
	textureCoords.resize(count * 2);

	indices.resize(6 * (VERTEX_COUNT -1)*(VERTEX_COUNT -1));

	int vertexIndex = 0;
	//X
	for (int i = 0; i < VERTEX_COUNT; i++) {

		//Z
		for (int j = 0; j < VERTEX_COUNT; j++) {
			vertices[vertexIndex * 3] = (float)j / ((float)VERTEX_COUNT - 1.0f) * SIZE;
			int height = HeightGenerator::generateHeight(j, i);
			heightMap[j][i] = height;
			//int height = height;
			vertices[vertexIndex * 3 + 1] = height;
			vertices[vertexIndex * 3 + 2] = (float)i / ((float)VERTEX_COUNT - 1.0f) * SIZE;


			//normals[vertexIndex * 3] = 0.0f;
			//normals[vertexIndex * 3 + 1] = 1.0f;
			//normals[vertexIndex * 3 + 2] = 0.0f;


			textureCoords[vertexIndex * 2] = (float)j / ((float)VERTEX_COUNT - 1.0f);
			textureCoords[vertexIndex * 2 + 1] = (float)i / ((float)VERTEX_COUNT - 1.0f);

			vertexIndex++;
		}

	}
	/*
	for (int i = 0; i < count; i += 9) {

		glm::vec3 v1(vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2]);
		glm::vec3 v2(vertices[i * 3 + 3], vertices[i * 3 + 4], vertices[i * 3 + 5]);
		glm::vec3 v3(vertices[i * 3 + 6], vertices[i * 3 + 7], vertices[i * 3 + 8]);

		//std::cout << vertices.size() << " " << (i + 2) * 3 << "\n";
		//
		glm::vec3 e1(v2 - v1);
		glm::vec3 e2(v3 - v1);

		glm::vec3 normal(glm::cross(e1, e2));

		
		normals[i * 3] = normal.x;
		normals[i * 3 + 1] = normal.y;
		normals[i * 3 + 2] = normal.z;

		normals[i * 3 + 3] = normal.x;
		normals[i * 3 + 4] = normal.y;
		normals[i * 3 + 5] = normal.z;

		normals[i * 3 + 6] = normal.x;
		normals[i * 3 + 7] = normal.y;
		normals[i * 3 + 8] = normal.z;
		
	}
	*/
	vertexIndex = 0;
	for (int z = 0; z < VERTEX_COUNT -1; z++) {
		for (int x = 0; x < VERTEX_COUNT - 1; x++) {
			int topLeft = (z * VERTEX_COUNT) + x;
			int topRight = topLeft + 1;

			int bottomLeft = ((z + 1) * VERTEX_COUNT) + x;
			int bottomRight = bottomLeft + 1;

			indices[vertexIndex++] = topLeft;
			indices[vertexIndex++] = bottomLeft;
			indices[vertexIndex++] = topRight;
			indices[vertexIndex++] = topRight;
			indices[vertexIndex++] = bottomLeft;
			indices[vertexIndex++] = bottomRight;

		}
	}
	//*/
	Mesh *mesh = Loader::loadToVAO(vertices, textureCoords, normals, indices);
	return mesh;
}


Mesh * Terrain::generateTerrain2()
{

	std::vector<glm::vec3> heights;
	HeightGenerator::generateFractalHeights(heights);

	int heightsSize = heights.size();

	int count = heightsSize * heightsSize;

	std::vector<float> vertices = { -0.5f,-0.5f,0.0f,
		0.5f,-0.5f,0.0f,
		0.0f,0.5f,0.0f };
	std::vector<float> normals = { 0.0f,1.0f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,1.0f,0.0f };
	std::vector<float> textureCoords = { -0.5f,-0.5f,
		0.5f,-0.5f,
		0.0f,0.5f };
	std::vector<int> indices = { 0, 1, 2 };
	///*
	vertices.resize(count * 3);
	normals.resize(count * 3);
	textureCoords.resize(count * 2);

	indices.resize(6 * (heightsSize - 1)*(heightsSize - 1));

	int vertexIndex = 0;
	for (int i = 0; i < heightsSize; i++) {

		for (int j = 0; j < heightsSize; j++) {
			vertices[vertexIndex * 3] = (float)j / ((float)heightsSize - 1.0f) * SIZE;
			//int height = HeightGenerator::generateHeight(j, i);
			int height = heights[i].y;
			vertices[vertexIndex * 3 + 1] = height;
			vertices[vertexIndex * 3 + 2] = (float)i / ((float)heightsSize - 1.0f) * SIZE;


			//normals[vertexIndex * 3] = 0.0f;
			//normals[vertexIndex * 3 + 1] = 1.0f;
			//normals[vertexIndex * 3 + 2] = 0.0f;


			textureCoords[vertexIndex * 2] = (float)j / ((float)heightsSize - 1.0f);
			textureCoords[vertexIndex * 2 + 1] = (float)i / ((float)heightsSize - 1.0f);

			vertexIndex++;
		}

	}
	/*
	for (int i = 0; i < count; i += 9) {

	glm::vec3 v1(vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2]);
	glm::vec3 v2(vertices[i * 3 + 3], vertices[i * 3 + 4], vertices[i * 3 + 5]);
	glm::vec3 v3(vertices[i * 3 + 6], vertices[i * 3 + 7], vertices[i * 3 + 8]);

	//std::cout << vertices.size() << " " << (i + 2) * 3 << "\n";
	//
	glm::vec3 e1(v2 - v1);
	glm::vec3 e2(v3 - v1);

	glm::vec3 normal(glm::cross(e1, e2));


	normals[i * 3] = normal.x;
	normals[i * 3 + 1] = normal.y;
	normals[i * 3 + 2] = normal.z;

	normals[i * 3 + 3] = normal.x;
	normals[i * 3 + 4] = normal.y;
	normals[i * 3 + 5] = normal.z;

	normals[i * 3 + 6] = normal.x;
	normals[i * 3 + 7] = normal.y;
	normals[i * 3 + 8] = normal.z;

	}
	*/
	vertexIndex = 0;
	for (int z = 0; z < heightsSize - 1; z++) {
		for (int x = 0; x < heightsSize - 1; x++) {
			int topLeft = (z * heightsSize) + x;
			int topRight = topLeft + 1;

			int bottomLeft = ((z + 1) * heightsSize) + x;
			int bottomRight = bottomLeft + 1;

			indices[vertexIndex++] = topLeft;
			indices[vertexIndex++] = bottomLeft;
			indices[vertexIndex++] = topRight;
			indices[vertexIndex++] = topRight;
			indices[vertexIndex++] = bottomLeft;
			indices[vertexIndex++] = bottomRight;

		}
	}
	//*/
	Mesh *mesh = Loader::loadToVAO(vertices, textureCoords, normals, indices);
	return mesh;
}

Mesh * Terrain::getMesh()
{
	return m_mesh;
}

