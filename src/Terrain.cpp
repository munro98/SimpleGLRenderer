#include "Terrain.hpp"



Terrain::Terrain()
{
	m_mesh = generateTerrain3();
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

// Midpoint Displacement
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

			int height = heights[i].y;
			//int height = heights[i][j].y;
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
	///*
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
	//*/
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

// Diamond Square
Mesh * Terrain::generateTerrain3()
{

	float heightMap[VERTEX_COUNT][VERTEX_COUNT] = {};
	//HeightGenerator::generateDiamondSquareHeights((float*)&heightMap);

	//Seed corners
	//heightMap[0][0] = HeightGenerator::random() * 50;
	//heightMap[0][VERTEX_COUNT - 1] = HeightGenerator::random() * 50;
	//heightMap[VERTEX_COUNT - 1][0] = HeightGenerator::random() * 50;
	//heightMap[VERTEX_COUNT - 1][VERTEX_COUNT - 1] = HeightGenerator::random() * 50;

	//Diamond
	//heightMap[VERTEX_COUNT / 2][VERTEX_COUNT / 2] = (heightMap[0][0] + heightMap[0][VERTEX_COUNT - 1] + heightMap[VERTEX_COUNT - 1][0] + heightMap[VERTEX_COUNT - 1][VERTEX_COUNT - 1]) / 4 + HeightGenerator::random() * 50;

	float roughness = 100;
	float min, max;
	int lod = TERRAIN_LOD;
	int divisions = 1 << lod;
	//float * terrain = new float[divisions + 1][divisions + 1];
	heightMap[0][0] = HeightGenerator::random();
	heightMap[0][divisions] = HeightGenerator::random();
	heightMap[divisions][divisions] = HeightGenerator::random();
	heightMap[divisions][0] = HeightGenerator::random();
	float rough = roughness;
	for (int i = 0; i < lod; ++i) {
		int q = 1 << i, r = 1 << (lod - i), s = r >> 1;
		for (int j = 0; j < divisions; j += r)
			for (int k = 0; k < divisions; k += r) {
				//diamond(j, k, r, rough)
				int x = j;
				int y = k;
				int side = r;
				if (side > 1) {
					int half = side / 2;
					float avg = (heightMap[x][y] + heightMap[x + side][y] +
						heightMap[x + side][y + side] + heightMap[x][y + side]) * 0.25;
					heightMap[x + half][y + half] = avg + HeightGenerator::random() * rough;
				}

			}
		if (s > 0)
			for (int j = 0; j <= divisions; j += s)
				for (int k = (j + s) % r; k <= divisions; k += r) {
					//square(j - s, k - s, r, rough);
					int x = j - s;
					int y = k - s;

					int side = r;
					int half = side / 2;
					float avg = 0.0, sum = 0.0;
					if (x >= 0)
					{
						avg += heightMap[x][y + half]; sum += 1.0;
					}
					if (y >= 0)
					{
						avg += heightMap[x + half][y]; sum += 1.0;
					}
					if (x + side <= divisions)
					{
						avg += heightMap[x + side][y + half]; sum += 1.0;
					}
					if (y + side <= divisions)
					{
						avg += heightMap[x + half][y + side]; sum += 1.0;
					}
					heightMap[x + half][y + half] = avg / sum + HeightGenerator::random() * rough;
				}

		rough /= 2;
	}
	min = max = heightMap[0][0];
	for (int i = 0; i <= divisions; ++i)
		for (int j = 0; j <= divisions; ++j)
			if (heightMap[i][j] < min)
				min = heightMap[i][j];
			else if (heightMap[i][j] > max)
				max = heightMap[i][j];



	int count = VERTEX_COUNT * VERTEX_COUNT;

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

	indices.resize(6 * (VERTEX_COUNT - 1)*(VERTEX_COUNT - 1));

	int vertexIndex = 0;
	//X
	for (int i = 0; i < VERTEX_COUNT; i++) {

		//Z
		for (int j = 0; j < VERTEX_COUNT; j++) {
			vertices[vertexIndex * 3] = (float)j / ((float)VERTEX_COUNT - 1.0f) * SIZE;
			int height = heightMap[j][i];
			//heightMap[j][i] = height;
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
	std::cout << normals.size() << "\n";
	for (int i = 0; i < vertices.size(); i += 9) {
		glm::vec3 v1(vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2]);
		glm::vec3 v2(vertices[i * 3 + 3], vertices[i * 3 + 4], vertices[i * 3 + 5]);
		glm::vec3 v3(vertices[i * 3 + 6], vertices[i * 3 + 7], vertices[i * 3 + 8]);
	
	


	//std::cout << vertices.size() << " " << (i + 2) * 3 << "\n";
	//
	/
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
	for (int z = 0; z < VERTEX_COUNT - 1; z++) {
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

Mesh * Terrain::getMesh()
{
	return m_mesh;
}

