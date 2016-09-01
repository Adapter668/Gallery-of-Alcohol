#include "SceneBuilder.h"
#include "lodepng.h"

vector<cuboid> SceneBuilder::all_models_coordinates;

void SceneBuilder::LoadModelsToMemory()
{
	objects[CUBE].mesh.LoadMesh("cube.obj", objects[0].outVert, objects[0].outNorm, objects[0].outUV);
	objects[CURACAO_BOTTLE].mesh.LoadMesh("bourbonBottle.obj", objects[1].outVert, objects[1].outNorm, objects[1].outUV);
    //objects[WHISKEY_BOTTLE].mesh.LoadMesh("whiskeyBottle.obj", objects[2].outVert, objects[2].outNorm, objects[2].outUV);
    objects[WHISKY_BOTTLE].mesh.LoadMesh("whiskyBottle.obj", objects[3].outVert, objects[3].outNorm, objects[3].outUV);
    //objects[WINE_BOTTLE].mesh.LoadMesh("wineBottle.obj", objects[4].outVert, objects[4].outNorm, objects[4].outUV);
    objects[WINE_BOTTLE2].mesh.LoadMesh("wineBottle2.obj", objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    objects[WINE_BOTTLE3].mesh.LoadMesh("wineBottle3.obj", objects[6].outVert, objects[6].outNorm, objects[6].outUV);


    //Reading and import image and place in initOpenGLProgram
    //Reading into CPU memory
    //Read texture image
    unsigned error0 = lodepng::decode(image0, width0, height0, "czerwony.png");
    unsigned error1 = lodepng::decode(image1, width1, height1, "rozowy.png");
    unsigned error2 = lodepng::decode(image2, width2, height2, "niebieski.png");
    unsigned error3 = lodepng::decode(image3, width3, height3, "green.png");
    unsigned error4 = lodepng::decode(image4, width4, height4, "brown.png");
    unsigned error5 = lodepng::decode(image5, width5, height5, "red.png");
    unsigned error6 = lodepng::decode(image6, width6, height6, "zielony.png");

    //Import into graphics card memory
    glGenTextures(1, &tex); //Initialize one handle
    glBindTexture(GL_TEXTURE_2D, tex); //Activate handle
}

void SceneBuilder::DrawObject(vector<float> outVert, vector<float> outNorm, vector<float> outUV)
{
	glEnableClientState(GL_VERTEX_ARRAY); //Tell OpenGL to use vertex coordinate array for drawing
										  //glEnableClientState(GL_COLOR_ARRAY); //Tell OpenGL to use color array for drawing
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, outVert.data());
	glNormalPointer(GL_FLOAT, 0, outNorm.data());
	glTexCoordPointer(2, GL_FLOAT, 0, outUV.data());
	glDrawArrays(GL_TRIANGLES, 0, outVert.size() / 3);
	glDisableClientState(GL_VERTEX_ARRAY); //Tell OpenGL to not use vertex coordinate array for drawing anymore
										   //glDisableClientState(GL_COLOR_ARRAY); //Tell OpenGL to not use color array for drawing anymore
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

mat4 SceneBuilder::Adjust(mat4 M, vec3 r, vec3 t, vec3 s)
{
    cuboid object;
	M = mat4(1.0f);
	//M = rotate(M, -1.0f, r);
	M = translate(M, t);
	M = scale(M, s);

    // coordinates of object:
    // back
    object.back_1.x = t.x + s.x * WIDTH_OF_CUBE/2;
    object.back_1.y = t.y + s.y * WIDTH_OF_CUBE/2;
    object.back_1.z = t.z + s.z * WIDTH_OF_CUBE/2;
    object.back_2.x = t.x - s.x * WIDTH_OF_CUBE/2;
    object.back_2.y = t.y + s.y * WIDTH_OF_CUBE/2;
    object.back_2.z = t.z + s.z * WIDTH_OF_CUBE/2;
    object.back_3.x = t.x  - s.x * WIDTH_OF_CUBE/2;
    object.back_3.y = t.y - s.y * WIDTH_OF_CUBE/2;
    object.back_3.z = t.z + s.z * WIDTH_OF_CUBE/2;
    object.back_4.x = t.x + s.x * WIDTH_OF_CUBE/2;
    object.back_4.y = t.y  - s.y * WIDTH_OF_CUBE/2;
    object.back_4.z = t.z + s.z * WIDTH_OF_CUBE/2;
    // front
    object.front_1.x = t.x + s.x * WIDTH_OF_CUBE/2;
    object.front_1.y = t.y + s.y * WIDTH_OF_CUBE/2;
    object.front_1.z = t.z - s.z * WIDTH_OF_CUBE/2;
    object.front_2.x = t.x - s.x * WIDTH_OF_CUBE/2;
    object.front_2.y = t.y + s.y * WIDTH_OF_CUBE/2;
    object.front_2.z = t.z- s.z * WIDTH_OF_CUBE/2;
    object.front_3.x = t.x - s.x * WIDTH_OF_CUBE/2;
    object.front_3.y = t.y - s.y * WIDTH_OF_CUBE/2;
    object.front_3.z = t.z - s.z * WIDTH_OF_CUBE/2;
    object.front_4.x = t.x + s.x * WIDTH_OF_CUBE/2;
    object.front_4.y = t.y - s.y * WIDTH_OF_CUBE/2;
    object.front_4.z = t.z - s.z * WIDTH_OF_CUBE/2;

    SceneBuilder::all_models_coordinates.push_back(object);

	return M;
}

void SceneBuilder::BuildScene(mat4 V)
{
    ApplyTexture(tex, image0, width0, height0); //czerwony
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(1.0f, 0.0f, 0.0f), vec3(-3.0f, 0.3f, 5.7f), vec3(2.0f, 0.3f, 0.3f)))); //naro�nik d�u�sza �ciana
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(1.0f, 0.0f, 0.0f), vec3(-1.3f, 0.3f, 4.5f), vec3(0.3f, 0.3f, 1.0f)))); //naro�nik kr�tsza �ciana
    DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(1.0f, 0.0f, 0.0f), vec3(-6.0f, 0.4f, 3.0f), vec3(0.3f, 0.4f, 0.3f)))); //st� w pokoju z naro�nikiem
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 1.5f, 5.6f), vec3(1.0f, 0.05f, 0.2f)))); //g�rna p�ka w korytarzu 
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 0.7f, 5.6f), vec3(1.0f, 0.05f, 0.2f)))); //dolna p�ka w korytarzu
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(1.0f, 0.0f, 0.0f), vec3(-6.0f, 1.5f, 0.2f), vec3(2.0f, 0.05f, 0.2f)))); //g�rna p�ka w pokoju z naro�nikiem
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(1.0f, 0.0f, 0.0f), vec3(-6.0f, 0.7f, 0.2f), vec3(2.0f, 0.05f, 0.2f)))); //dolna p�ka w pokoju z naro�nikiem
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(1.0f, 0.0f, 0.0f), vec3(-0.5f, 1.5f, -3.0f), vec3(0.2f, 0.05f, 3.0f)))); //g�rna p�ka w pokoju z barem
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(1.0f, 0.0f, 0.0f), vec3(-0.5f, 0.5f, -3.0f), vec3(0.2f, 0.05f, 3.0f)))); //dolna p�ka w pokoju z barem
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(1.0f, 0.0f, 0.0f), vec3(-2.0f, 0.4f, -4.0f), vec3(0.3f, 0.4f, 0.3f)))); //st� pok�j z barem
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(1.0f, 0.0f, 0.0f), vec3(-2.0f, 0.4f, -2.0f), vec3(0.3f, 0.4f, 0.3f)))); //st� pok�j z barem
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(1.0f, 0.0f, 0.0f), vec3(-4.5f, 0.4f, -4.0f), vec3(0.3f, 0.4f, 0.3f)))); //st� pok�j z barem
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(1.0f, 0.0f, 0.0f), vec3(-4.5f, 0.4f, -2.0f), vec3(0.3f, 0.4f, 0.3f)))); //st� pok�j z barem
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(1.0f, 0.0f, 0.0f), vec3(-6.5f, 0.4f, -4.0f), vec3(0.2f, 0.4f, 2.0f)))); //bar
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);

	//slupki w malym pokoju
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(1.0f, 0.0f, 0.0f), vec3(4.0f, 0.3f, 3.5f), vec3(0.07f, 0.3f, 0.07f))));
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(1.0f, 0.0f, 0.0f), vec3(4.0f, 0.4f, 5.0f), vec3(0.07f, 0.4f, 0.07f))));
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(1.0f, 0.0f, 0.0f), vec3(5.0f, 0.4f, 3.5f), vec3(0.07f, 0.4f, 0.07f))));
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(1.0f, 0.0f, 0.0f), vec3(5.0f, 0.3f, 5.0f), vec3(0.07f, 0.3f, 0.07f))));
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(1.0f, 0.0f, 0.0f), vec3(6.0f, 0.3f, 3.5f), vec3(0.07f, 0.3f, 0.07f))));
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(1.0f, 0.0f, 0.0f), vec3(6.0f, 0.4f, 5.0f), vec3(0.07f, 0.4f, 0.07f))));
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(1.0f, 0.0f, 0.0f), vec3(7.0f, 0.4f, 3.5f), vec3(0.07f, 0.4f, 0.07f))));
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(1.0f, 0.0f, 0.0f), vec3(7.0f, 0.3f, 5.0f), vec3(0.07f, 0.3f, 0.07f))));
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(1.0f, 0.0f, 0.0f), vec3(3.5f, 0.3f, 2.7f), vec3(0.07f, 0.3f, 0.07f))));
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(1.0f, 0.0f, 0.0f), vec3(3.5f, 0.4f, 4.3f), vec3(0.07f, 0.4f, 0.07f))));
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(1.0f, 0.0f, 0.0f), vec3(4.5f, 0.4f, 2.7f), vec3(0.07f, 0.4f, 0.07f))));
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(1.0f, 0.0f, 0.0f), vec3(4.5f, 0.3f, 4.3f), vec3(0.07f, 0.3f, 0.07f))));
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(1.0f, 0.0f, 0.0f), vec3(5.5f, 0.3f, 2.7f), vec3(0.07f, 0.3f, 0.07f))));
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(1.0f, 0.0f, 0.0f), vec3(5.5f, 0.4f, 4.3f), vec3(0.07f, 0.4f, 0.07f))));
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(1.0f, 0.0f, 0.0f), vec3(6.5f, 0.4f, 2.7f), vec3(0.07f, 0.4f, 0.07f))));
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(1.0f, 0.0f, 0.0f), vec3(6.5f, 0.3f, 4.3f), vec3(0.07f, 0.3f, 0.07f))));
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);

	// maze
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(1.0f, 0.0f, 0.0f), vec3(4.0f, 0.5f, -1.6f), vec3(2.5f, 2.0f, 0.1f))));
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(1.0f, 0.0f, 0.0f), vec3(1.5f, 0.5f, -3.0f), vec3(0.1f, 2.0f, 1.5f))));
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(1.0f, 0.0f, 0.0f), vec3(3.5f, 0.5f, -4.4f), vec3(2.0f, 2.0f, 0.1f))));
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(1.0f, 0.0f, 0.0f), vec3(5.5f, 0.5f, -3.0f), vec3(2.5f, 2.0f, 0.1f))));
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);
    glDeleteTextures(1, &tex);

	// room:
    ApplyTexture(tex, image2, width2, height2); //niebieski
	// floor
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.1f,  0.0f), vec3(8.0f, 0.0f, 6.0f))));
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);

    glLoadMatrixf(value_ptr(V*Adjust(objects[1].M, vec3(0.0f, 0.0f, 0.0f), vec3(0.8f, 0.82f,  5.6f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[1].outVert, objects[1].outNorm, objects[1].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[1].M, vec3(0.0f, 0.0f, 0.0f), vec3(0.6f, 0.82f,  5.6f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[1].outVert, objects[1].outNorm, objects[1].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[1].M, vec3(0.0f, 0.0f, 0.0f), vec3(0.4f, 0.82f,  5.6f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[1].outVert, objects[1].outNorm, objects[1].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[1].M, vec3(0.0f, 0.0f, 0.0f), vec3(0.2f, 0.82f,  5.6f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[1].outVert, objects[1].outNorm, objects[1].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[1].M, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.82f,  5.6f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[1].outVert, objects[1].outNorm, objects[1].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[1].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.2f, 0.82f,  5.6f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[1].outVert, objects[1].outNorm, objects[1].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[1].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.4f, 0.82f,  5.6f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[1].outVert, objects[1].outNorm, objects[1].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[1].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.82f,  5.6f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[1].outVert, objects[1].outNorm, objects[1].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[1].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.8f, 0.82f,  5.6f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[1].outVert, objects[1].outNorm, objects[1].outUV);

    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -3.9f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -4.0f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -4.1f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -4.2f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -4.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -4.4f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -4.5f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -4.6f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -4.7f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -4.8f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -4.9f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -5.0f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -5.1f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -5.2f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -5.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -5.4f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -5.5f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -5.6f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -5.7f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -5.8f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);

    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -3.9f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -4.0f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -4.1f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -4.2f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -4.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -4.4f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -4.5f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -4.6f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -4.7f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -4.8f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -4.9f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -5.0f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -5.1f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -5.2f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -5.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -5.4f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -5.5f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -5.6f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -5.7f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -5.8f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);

    glLoadMatrixf(value_ptr(V*Adjust(objects[1].M, vec3(0.0f, 0.0f, 0.0f), vec3(-5.9f, 0.87f,  3.1f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[1].outVert, objects[1].outNorm, objects[1].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[1].M, vec3(0.0f, 0.0f, 0.0f), vec3(-1.9f, 0.87f,  -2.0f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[1].outVert, objects[1].outNorm, objects[1].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[1].M, vec3(0.0f, 0.0f, 0.0f), vec3(-4.4f, 0.87f,  -2.0f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[1].outVert, objects[1].outNorm, objects[1].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[1].M, vec3(0.0f, 0.0f, 0.0f), vec3(-1.9f, 0.87f,  -4.0f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[1].outVert, objects[1].outNorm, objects[1].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[1].M, vec3(0.0f, 0.0f, 0.0f), vec3(-4.4f, 0.87f,  -4.0f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[1].outVert, objects[1].outNorm, objects[1].outUV);

    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(3.5f, 0.95f,  4.3f), vec3(0.1f, 0.13f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(4.5f, 0.95f,  2.7f), vec3(0.1f, 0.13f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(5.5f, 0.95f,  4.3f), vec3(0.1f, 0.13f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(6.5f, 0.95f,  2.7f), vec3(0.1f, 0.13f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);

    ApplyTexture(tex, image1, width1, height1); //różowy
	// main walls
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f,  6.0f), vec3(8.0f, 2.0f, 0.1f))));
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f,  -6.0f), vec3(8.0f, 2.0f, 0.1f))));
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(0.0f, 0.0f, 0.0f), vec3(8.0f, 0.0f,  0.0f), vec3(0.1f, 2.0f, 6.0f))));
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(0.0f, 0.0f, 0.0f), vec3(-8.0f, 0.0f,  0.0f), vec3(0.1f, 2.0f, 6.0f))));
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);
	// inner walls
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.25f, 0.0f,  -3.0f), vec3(0.1f, 2.0f, 3.0f))));
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(0.0f, 0.0f, 0.0f), vec3(-6.0f, 0.0f,  0.0f), vec3(2.0f, 2.0f, 0.1f))));
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f,  4.0f), vec3(0.1f, 2.0f, 2.0f))));
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);

    ApplyTexture(tex, image3, width3, height3); //green
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(0.8f, 1.62f,  5.6f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(0.7f, 1.62f,  5.6f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(0.6f, 1.62f,  5.6f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(0.5f, 1.62f,  5.6f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(0.4f, 1.62f,  5.6f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(0.3f, 1.62f,  5.6f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(0.2f, 1.62f,  5.6f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(0.1f, 1.62f,  5.6f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.62f,  5.6f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.1f, 1.62f,  5.6f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.2f, 1.62f,  5.6f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.3f, 1.62f,  5.6f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.4f, 1.62f,  5.6f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.5f, 1.62f,  5.6f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.62f,  5.6f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.7f, 1.62f,  5.6f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.8f, 1.62f,  5.6f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.9f, 1.62f,  5.6f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);

    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -0.1f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -0.2f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -0.4f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -0.5f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -0.6f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -0.7f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -0.8f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -0.9f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -1.0f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -1.1f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -1.2f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -1.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -1.4f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -1.5f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -1.6f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -1.7f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -1.8f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -1.9f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);


    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -0.1f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -0.2f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -0.4f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -0.5f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -0.6f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -0.7f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -0.8f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -0.9f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -1.0f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -1.1f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -1.2f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -1.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -1.4f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -1.5f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -1.6f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -1.7f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -1.8f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -1.9f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);

    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(4.0f, 0.7f,  3.5f), vec3(0.1f, 0.08f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(6.0f, 0.7f,  3.5f), vec3(0.1f, 0.08f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(7.0f, 0.7f,  5.0f), vec3(0.1f, 0.08f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(5.0f, 0.7f,  5.0f), vec3(0.1f, 0.08f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);


    ApplyTexture(tex, image4, width4, height4); //brown
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-4.1f, 1.67f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-4.3f, 1.67f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-4.5f, 1.67f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-4.7f, 1.67f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-4.9f, 1.67f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-5.1f, 1.67f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-5.3f, 1.67f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-5.5f, 1.67f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-5.7f, 1.67f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-5.9f, 1.67f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-6.1f, 1.67f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-6.3f, 1.67f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-6.5f, 1.67f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-6.7f, 1.67f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-6.9f, 1.67f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-7.1f, 1.67f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-7.3f, 1.67f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-7.5f, 1.67f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-7.7f, 1.67f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);

    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-4.1f, 0.87f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-4.3f, 0.87f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-4.5f, 0.87f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-4.7f, 0.87f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-4.9f, 0.87f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-5.1f, 0.87f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-5.3f, 0.87f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-5.5f, 0.87f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-5.7f, 0.87f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-5.9f, 0.87f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-6.1f, 0.87f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-6.3f, 0.87f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-6.5f, 0.87f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-6.7f, 0.87f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-6.9f, 0.87f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-7.1f, 0.87f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-7.3f, 0.87f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-7.5f, 0.87f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-7.7f, 0.87f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);

    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-6.1f, 0.92f,  2.9f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-2.1f, 0.92f,  -1.9f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-4.6f, 0.92f,  -1.9f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-2.1f, 0.92f,  -4.1f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-4.6f, 0.92f,  -4.1f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);

    glLoadMatrixf(value_ptr(V*Adjust(objects[1].M, vec3(0.0f, 0.0f, 0.0f), vec3(4.0f, 0.89f,  5.0f), vec3(0.1f, 0.12f, 0.15f))));
    DrawObject(objects[1].outVert, objects[1].outNorm, objects[1].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[1].M, vec3(0.0f, 0.0f, 0.0f), vec3(5.0f, 0.89f,  3.5f), vec3(0.1f, 0.12f, 0.15f))));
    DrawObject(objects[1].outVert, objects[1].outNorm, objects[1].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[1].M, vec3(0.0f, 0.0f, 0.0f), vec3(6.0f, 0.89f,  5.0f), vec3(0.1f, 0.12f, 0.15f))));
    DrawObject(objects[1].outVert, objects[1].outNorm, objects[1].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[1].M, vec3(0.0f, 0.0f, 0.0f), vec3(7.0f, 0.89f,  3.5f), vec3(0.1f, 0.12f, 0.15f))));
    DrawObject(objects[1].outVert, objects[1].outNorm, objects[1].outUV);


    ApplyTexture(tex, image5, width5, height5); //red
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-4.2f, 1.67f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-4.4f, 1.67f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-4.6f, 1.67f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-4.8f, 1.67f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-5.0f, 1.67f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-5.2f, 1.67f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-5.4f, 1.67f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-5.6f, 1.67f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-5.8f, 1.67f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-6.0f, 1.67f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-6.2f, 1.67f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-6.4f, 1.67f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-6.6f, 1.67f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-6.8f, 1.67f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-7.0f, 1.67f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-7.2f, 1.67f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-7.4f, 1.67f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-7.6f, 1.67f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);

    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-4.2f, 0.87f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-4.4f, 0.87f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-4.6f, 0.87f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-4.8f, 0.87f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-5.0f, 0.87f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-5.2f, 0.87f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-5.4f, 0.87f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-5.6f, 0.87f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-5.8f, 0.87f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-6.0f, 0.87f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-6.2f, 0.87f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-6.4f, 0.87f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-6.6f, 0.87f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-6.8f, 0.87f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-7.0f, 0.87f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-7.2f, 0.87f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-7.4f, 0.87f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-7.6f, 0.87f,  0.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);

    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -2.0f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -2.1f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -2.2f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -2.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -2.4f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -2.5f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -2.6f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -2.7f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -2.8f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -2.9f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -3.0f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -3.1f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -3.2f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -3.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -3.4f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -3.5f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -3.6f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -3.7f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 1.67f,  -3.8f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);

    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -2.0f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -2.1f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -2.2f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -2.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -2.4f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -2.5f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -2.6f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -2.7f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -2.8f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -2.9f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -3.0f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -3.1f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -3.2f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -3.3f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -3.4f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -3.5f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -3.6f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -3.7f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(-0.6f, 0.67f,  -3.8f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);

    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-5.9f, 0.92f,  2.9f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-1.9f, 0.92f,  -1.9f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-4.4f, 0.92f,  -1.9f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-1.9f, 0.92f,  -4.1f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[6].M, vec3(0.0f, 0.0f, 0.0f), vec3(-4.4f, 0.92f,  -4.1f), vec3(0.1f, 0.1f, 0.1f))));
    DrawObject(objects[6].outVert, objects[6].outNorm, objects[6].outUV);

    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(3.5f, 0.77f,  2.7f), vec3(0.1f, 0.15f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(4.5f, 0.77f,  4.3f), vec3(0.1f, 0.15f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(5.5f, 0.77f,  2.7f), vec3(0.1f, 0.15f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);
    glLoadMatrixf(value_ptr(V*Adjust(objects[5].M, vec3(0.0f, 0.0f, 0.0f), vec3(6.5f, 0.77f,  4.3f), vec3(0.1f, 0.15f, 0.1f))));
    DrawObject(objects[5].outVert, objects[5].outNorm, objects[5].outUV);


    glDeleteTextures(1, &tex);
}


void SceneBuilder::ApplyTexture(GLuint tex, std::vector<unsigned char> image, unsigned width, unsigned height) {
    //Import image into memory associated with the handle
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glEnable(GL_TEXTURE_2D);

}
