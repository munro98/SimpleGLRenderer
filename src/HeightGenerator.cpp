#include "HeightGenerator.hpp"
#include <cmath>
#include <iostream>



HeightGenerator::HeightGenerator()
{
}

HeightGenerator::~HeightGenerator()
{
}

int HeightGenerator::generateHeight(int x, int z)
{
	//return generateSmoothNoise(x, z);
	float value = generateInterpolatedNoise((float)x / 8.0f, (float)z / 8.0f) * AMPLITUDE;
	//std::cout << value << "\n";
	return value;
}

float HeightGenerator::generateInterpolatedNoise(float x, float z)
{
	int intX = (int)std::floor(x);
	int intZ = (int)std::floor(z);
	float fracX = x - intX;
	float fracZ = z - intZ;

	float v1 = generateSmoothNoise(intX, intZ);
	float v2 = generateSmoothNoise(intX + 1, intZ);
	float v3 = generateSmoothNoise(intX, intZ + 1);
	float v4 = generateSmoothNoise(intX + 1, intZ + 1);

	float i1 = interpolate(v1, v2, fracX);
	float i2 = interpolate(v3, v4, fracX);
	return interpolate(i1, i2, fracZ);

	//float i1 = lerp(v1, v2, fracX);
	//float i2 = lerp(v3, v4, fracX);
	//return lerp(i1, i2, fracZ);
}

float HeightGenerator::interpolate(float a, float b, float blend)
{
	float theta = blend * PI;
	float f = (1.0f - cos(theta)) * 0.5f;
	return a * (1.0f - f) + b * f;
}

float HeightGenerator::lerp(float a, float b, float f)
{
	return a + f * (b - a);
}

float HeightGenerator::generateSmoothNoise(int x, int z)
{
	//float corners = (generateNoise2(x-1, z-1) + generateNoise2(x+1, z-1) + generateNoise2(x-1, z+1) + generateNoise2(x+1, z+1)) / 8.0f;
	//float sides = (generateNoise2(x - 1, z) + generateNoise2(x + 1, z) + generateNoise2(x, z - 1) + generateNoise2(x, z + 1)) / 4.0f;
	float center = generateNoise2(x, z);
	return center;// +corners;// + sides
	//return center + corners + sides;
}
/*
float HeightGenerator::generateNoise(int x, int z)
{
	//rng.seed(std::random_device()());
	static std::mt19937 rng;
	static std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
	rng.seed(x * 49632 + z * 325176);
	//rng.seed(Hasher::hash(x,z));

	//std::cout << dist(rng) << std::endl;
	float value = dist(rng);// *2.0f - 1.0f;
	//std::cout << value << "\n";
	return value;
}
*/

float HeightGenerator::generateNoise2(int x, int z)
{
	int value = (hash(x, z) % 128) - 64;
	float value2 = (float)value / 64.0f;
	//std::cout << value << "\n";
	return value2;
}


int HeightGenerator::hash(int key)
{
	key = ~key + (key << 15);
	key = key ^ (key >> 12);
	key = key + (key << 2);
	key = key ^ (key >> 4);
	key = key * 2048;
	key = key ^ (key >> 16);
	return key;
}

int HeightGenerator::hash(int x, int y)
{
	x = hash(x);
	y = hash(y);
	return hash(x ^ (y << 2));
}

glm::vec3 HeightGenerator::fractalSplit(glm::vec3 v1, glm::vec3 v2)
{
	glm::vec3 delta = v1 - v2;
	delta = delta * 0.5f;
	return v1 - delta;


}

float HeightGenerator::random()
{
	//rng.seed(std::random_device()());
	static std::mt19937 rng;
	static std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
	//rng.seed(x * 49632 + z * 325176);
	//std::cout << dist(rng) << std::endl;
	float value = dist(rng);

	return value;
}

void HeightGenerator::generateFractalHeights(std::vector<glm::vec3>& vertices)
{
	vertices.push_back(glm::vec3(0,0,0));
	//vertices.push_back(glm::vec3(50, 50, 0));
	vertices.push_back(glm::vec3(100, 0, 0));

	///*
	float randomSize = 50;

	for (int i = 0; i < 4; i++) {

		for (int j = 0; j < vertices.size() - 1;) {
			glm::vec3 v1 = vertices[j];
			glm::vec3 v2 = vertices[j+1];

			glm::vec3 v = fractalSplit(v1, v2);
			v.y = v.y + std::floor((random() * randomSize) + 1);

			vertices.emplace(vertices.begin() + j + 1, v);
			j += 2;
		}
		randomSize /= 2;
	}
	//*/

}


void HeightGenerator::generateDiamondSquareHeights(float *heights)
{
	*heights = random() * 50;

}