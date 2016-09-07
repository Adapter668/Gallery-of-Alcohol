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
#include "meshLoader.h"

using namespace glm;

struct furnitureAndBottles {
	MeshLoader mesh;
	vector<float> outVert;
	vector<float> outNorm;
	vector<float> outUV;
	mat4 M;
};

struct  cuboid {
    vec3 front_1;
    vec3 front_2;
    vec3 front_3;
    vec3 front_4;
    vec3 back_1;
    vec3 back_2;
    vec3 back_3;
    vec3 back_4;
};

struct bottle {
    vec3 center;
    float width;
    float height;
    int type;
};

class SceneBuilder
{
private:
    furnitureAndBottles objects[2];                                 // array of models types
    GLuint tex;
    std::vector<unsigned char> image0, image1, image2, image3, image4, image5, image6; //Allocate a vector for image data
    unsigned width0, height0, width1, height1, width2, height2, width3, height3, width4, height4, width5, height5, width6, height6; //Variables for image size
    bool load_first_models = true;
    bool load_first_bottles = true;
	double my_time = 0;

    mat4 Adjust(mat4 M, vec3 r, vec3 t, vec3 s, int type = CUBE);
    void DrawObject(vector<float> outVert, vector<float> outNorm, vector<float> outUV);
    void ApplyTexture(GLuint tex, std::vector<unsigned char> image, unsigned width, unsigned height);
    void addObjectsToArray(mat4 M, vec3 r, vec3 t, vec3 s);
    void addBottlesToArray(mat4 M, vec3 r, vec3 t, vec3 s, int type);

public:
    static vector<cuboid> all_cuboid_models_coordinates;
    static vector<bottle> all_bottles_coordinates;
	bool swaying = false;

	SceneBuilder() { };
	~SceneBuilder() {};
	void LoadModelsToMemory();
	void BuildScene(mat4 V);
    void getObjectsOuts(short type, vector<float> &outVert, vector<float> &outNorm, vector<float> &outUV);
	void sway(short type);
};

