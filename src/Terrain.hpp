#pragma once
#include <glm/gtc/type_ptr.hpp>

#include "Model.hpp"
#include "Loader.hpp"
#include "HeightGenerator.hpp"
#define SIZE 400
//#define VERTEX_COUNT 64
#define TERRAIN_LOD 7
#define VERTEX_COUNT ((1 << TERRAIN_LOD) + 1)
//#define VERTEX_COUNT 33


class Terrain
{
public:
	Terrain();
	~Terrain();

	Mesh* generateTerrain();

	Mesh * generateTerrain2();

	Mesh * generateTerrain3();

	Mesh *getMesh();

private:
	Mesh * m_mesh;
};

