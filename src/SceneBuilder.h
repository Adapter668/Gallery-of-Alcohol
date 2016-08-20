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
#include "MeshLoader.h"

using namespace glm;

class SceneBuilder
{
public:
	/*MeshLoader mesh1;
	vector<float> outVert1;
	vector<float> outNorm1;
	vector<float> outUV1;
	mat4 M1 = mat4(1.0f);
	MeshLoader mesh2;
	vector<float> outVert2;
	vector<float> outNorm2;
	vector<float> outUV2;
	mat4 M2 = mat4(1.0f);*/
	
	//naro¿nik dalej od wejœcia
	MeshLoader mesh3;
	vector<float> outVert3;
	vector<float> outNorm3;
	vector<float> outUV3;
	mat4 M3 = mat4(1.0f);
	//naro¿nik przy wejœciu
	MeshLoader mesh4;
	vector<float> outVert4;
	vector<float> outNorm4;
	vector<float> outUV4;
	mat4 M4 = mat4(1.0f);
	//stolik w pokoju z naro¿nikiem
	MeshLoader mesh5;
	vector<float> outVert5;
	vector<float> outNorm5;
	vector<float> outUV5;
	mat4 M5 = mat4(1.0f);
	//górna pó³ka przedpokój
	MeshLoader mesh6;
	vector<float> outVert6;
	vector<float> outNorm6;
	vector<float> outUV6;
	mat4 M6 = mat4(1.0f);
	//dolna pó³ka przedpokój
	MeshLoader mesh7;
	vector<float> outVert7;
	vector<float> outNorm7;
	vector<float> outUV7;
	mat4 M7 = mat4(1.0f);
	//górna pó³ka pokój z naro¿nikiem
	MeshLoader mesh8;
	vector<float> outVert8;
	vector<float> outNorm8;
	vector<float> outUV8;
	mat4 M8 = mat4(1.0f);
	//dolna pó³ka pokój z naro¿nikiem
	MeshLoader mesh9;
	vector<float> outVert9;
	vector<float> outNorm9;
	vector<float> outUV9;
	mat4 M9 = mat4(1.0f);
	//górna pó³ka pokój z barem
	MeshLoader mesh10;
	vector<float> outVert10;
	vector<float> outNorm10;
	vector<float> outUV10;
	mat4 M10 = mat4(1.0f);
	//dolna pó³ka pokój z barem
	MeshLoader mesh11;
	vector<float> outVert11;
	vector<float> outNorm11;
	vector<float> outUV11;
	mat4 M11 = mat4(1.0f);
	//stolik od wejœcia dalszy z prawej pokój z barem
	MeshLoader mesh12;
	vector<float> outVert12;
	vector<float> outNorm12;
	vector<float> outUV12;
	mat4 M12 = mat4(1.0f);
	//stolik od wejœcia bli¿szy z prawej pokój z barem
	MeshLoader mesh13;
	vector<float> outVert13;
	vector<float> outNorm13;
	vector<float> outUV13;
	mat4 M13 = mat4(1.0f);
	//stolik od wejœcia dalszy z lewej pokój z barem
	MeshLoader mesh14;
	vector<float> outVert14;
	vector<float> outNorm14;
	vector<float> outUV14;
	mat4 M14 = mat4(1.0f);
	//stolik od wejœcia bli¿szy z lewej pokój z barem
	MeshLoader mesh15;
	vector<float> outVert15;
	vector<float> outNorm15;
	vector<float> outUV15;
	mat4 M15 = mat4(1.0f);
	//bar pokój z barem xD
	MeshLoader mesh16;
	vector<float> outVert16;
	vector<float> outNorm16;
	vector<float> outUV16;
	mat4 M16 = mat4(1.0f);
	//16 s³upków na kieliszki ma³y pokój
	MeshLoader mesh17a;
	vector<float> outVert17a;
	vector<float> outNorm17a;
	vector<float> outUV17a;
	mat4 M17a = mat4(1.0f);
	MeshLoader mesh17b;
	vector<float> outVert17b;
	vector<float> outNorm17b;
	vector<float> outUV17b;
	mat4 M17b = mat4(1.0f);
	MeshLoader mesh17c;
	vector<float> outVert17c;
	vector<float> outNorm17c;
	vector<float> outUV17c;
	mat4 M17c = mat4(1.0f);
	MeshLoader mesh17d;
	vector<float> outVert17d;
	vector<float> outNorm17d;
	vector<float> outUV17d;
	mat4 M17d = mat4(1.0f);
	MeshLoader mesh17e;
	vector<float> outVert17e;
	vector<float> outNorm17e;
	vector<float> outUV17e;
	mat4 M17e = mat4(1.0f);
	MeshLoader mesh17f;
	vector<float> outVert17f;
	vector<float> outNorm17f;
	vector<float> outUV17f;
	mat4 M17f = mat4(1.0f);
	MeshLoader mesh17g;
	vector<float> outVert17g;
	vector<float> outNorm17g;
	vector<float> outUV17g;
	mat4 M17g = mat4(1.0f);
	MeshLoader mesh17h;
	vector<float> outVert17h;
	vector<float> outNorm17h;
	vector<float> outUV17h;
	mat4 M17h = mat4(1.0f);
	MeshLoader mesh17i;
	vector<float> outVert17i;
	vector<float> outNorm17i;
	vector<float> outUV17i;
	mat4 M17i = mat4(1.0f);
	MeshLoader mesh17j;
	vector<float> outVert17j;
	vector<float> outNorm17j;
	vector<float> outUV17j;
	mat4 M17j = mat4(1.0f);
	MeshLoader mesh17k;
	vector<float> outVert17k;
	vector<float> outNorm17k;
	vector<float> outUV17k;
	mat4 M17k = mat4(1.0f);
	MeshLoader mesh17l;
	vector<float> outVert17l;
	vector<float> outNorm17l;
	vector<float> outUV17l;
	mat4 M17l = mat4(1.0f);
	MeshLoader mesh17m;
	vector<float> outVert17m;
	vector<float> outNorm17m;
	vector<float> outUV17m;
	mat4 M17m = mat4(1.0f);
	MeshLoader mesh17n;
	vector<float> outVert17n;
	vector<float> outNorm17n;
	vector<float> outUV17n;
	mat4 M17n = mat4(1.0f);
	MeshLoader mesh17o;
	vector<float> outVert17o;
	vector<float> outNorm17o;
	vector<float> outUV17o;
	mat4 M17o = mat4(1.0f);
	MeshLoader mesh17p;
	vector<float> outVert17p;
	vector<float> outNorm17p;
	vector<float> outUV17p;
	mat4 M17p = mat4(1.0f);
	//"labirynt"
	MeshLoader mesh18a;
	vector<float> outVert18a;
	vector<float> outNorm18a;
	vector<float> outUV18a;
	mat4 M18a = mat4(1.0f);
	MeshLoader mesh18b;
	vector<float> outVert18b;
	vector<float> outNorm18b;
	vector<float> outUV18b;
	mat4 M18b = mat4(1.0f);
	MeshLoader mesh18c;
	vector<float> outVert18c;
	vector<float> outNorm18c;
	vector<float> outUV18c;
	mat4 M18c = mat4(1.0f);
	MeshLoader mesh18d;
	vector<float> outVert18d;
	vector<float> outNorm18d;
	vector<float> outUV18d;
	mat4 M18d = mat4(1.0f);

	SceneBuilder();
	~SceneBuilder();
	void LoadModels();
	void DrawObject(vector<float> outVert, vector<float> outNorm, vector<float> outUV);
	mat4 Adjust(mat4 M, vec3 r, vec3 t, vec3 s);
	void InProgress(mat4 V); //it will be the BuildScene procedure, but now is InProgress
};

