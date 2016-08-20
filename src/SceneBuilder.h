#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "constants.h"
#include "MeshLoader.h"

using namespace glm;

struct furnitureAndBottles {
	MeshLoader mesh;
	vector<float> outVert;
	vector<float> outNorm;
	vector<float> outUV;
	mat4 M;
};

class SceneBuilder
{
public:

	furnitureAndBottles objects[2];

	SceneBuilder();
	~SceneBuilder();
	void LoadModels();
	void DrawObject(vector<float> outVert, vector<float> outNorm, vector<float> outUV);
	mat4 Adjust(mat4 M, vec3 r, vec3 t, vec3 s);
	void InProgress(mat4 V); //it will be the BuildScene procedure, but now is InProgress
};

