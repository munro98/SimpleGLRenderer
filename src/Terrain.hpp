
#include <glm/gtc/type_ptr.hpp>

#include "Model.hpp"
#include "Loader.hpp"
#include "HeightGenerator.hpp"
#define SIZE 400
#define VERTEX_COUNT 64

class Terrain
{
public:
	Terrain();
	~Terrain();

	Mesh* generateTerrain();

	Mesh *getMesh();

private:
	Mesh * m_mesh;
};

