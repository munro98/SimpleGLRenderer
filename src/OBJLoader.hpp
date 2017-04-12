#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.hpp"



class OBJLoader
{
public:
	OBJLoader();
	~OBJLoader();
	static Mesh * loadObjModel(const std::string & fileName);
	static void processVertex(int vi1, int vi2, int vi3, std::vector<int>& indices, std::vector<glm::vec2>& textures, std::vector<glm::vec3>& normals, std::vector<float>& texturesArray, std::vector<float> normalsArray);
	//static void processVertex(int vi1, int vi2, int vi3, std::vector<int>& indices, std::vector<sf::Vector2f>& textures, std::vector<sf::Vector3f>& normals, std::unique_ptr<float[]>& texturesArray, std::unique_ptr<float[]>& normalsArray);
	//static void processVertex(int vi1, int vi2, int vi3, std::vector<int>& indices, std::vector<sf::Vector2f>& textures, std::vector<sf::Vector3f>& normals, float*, float* normalsArray);
};

