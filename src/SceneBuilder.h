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

struct  cuboid {
    vec2 front_1;
    vec2 front_2;
    vec2 front_3;
    vec2 front_4;
    vec2 back_1;
    vec2 back_2;
    vec2 back_3;
    vec2 back_4;
};

class SceneBuilder
{
private:
    furnitureAndBottles objects[2];                                 // array of models types
    int currentInAll_Models = 0;
    float widthOfCube = WIDTH_OF_CUBE;
    GLuint tex;

    mat4 Adjust(mat4 M, vec3 r, vec3 t, vec3 s);
    void DrawObject(vector<float> outVert, vector<float> outNorm, vector<float> outUV);
    void addModelToArrayAll_Models(mat4 V, vec3 rotate, vec3 transform, vec3 scale);


public:
    cuboid all_models[30];
    std::vector<unsigned char> image0, image1, image2; //Allocate a vector for image data
    unsigned width0, height0, width1, height1, width2, height2; //Variables for image size

	SceneBuilder();
	~SceneBuilder();
	void LoadModels();
	void InProgress(mat4 V); //it will be the BuildScene procedure, but now is InProgress
    void TextureTryToDo(GLuint tex, std::vector<unsigned char> image, unsigned width, unsigned height);
};

