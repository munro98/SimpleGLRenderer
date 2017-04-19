#pragma once
#define PI 3.1415926535897932384626433832795 
#define AMPLITUDE 64.0f
#include <random>
#include <glm/gtc/type_ptr.hpp>


#include "Math.h"

class HeightGenerator
{
public:
	HeightGenerator();
	~HeightGenerator();

	static int generateHeight(int x, int z);
	static float generateInterpolatedNoise(float x, float z);
	static float interpolate(float a, float b, float blend);
	static float lerp(float a, float b, float f);
	static float generateSmoothNoise(int x, int z);
	static float generateNoise(int x, int z);

	static float generateNoise2(int x, int z);

	static int hash(int key);

	static int hash(int x, int y);

	static glm::vec3 fractalSplit(glm::vec3 v1, glm::vec3 v2);

	static float random();

	static void generateFractalHeights(std::vector<glm::vec3>& height);

};

