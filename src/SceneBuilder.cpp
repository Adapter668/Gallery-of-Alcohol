#include "SceneBuilder.h"
#include "lodepng.h"

SceneBuilder::SceneBuilder()  {
}

SceneBuilder::~SceneBuilder()  {
}

void SceneBuilder::addModelToArrayAll_Models(mat4 V, vec3 rotate, vec3 transform, vec3 scale) {
}

void SceneBuilder::LoadModels()
{
	objects[CUBE].mesh.LoadMesh("cube.obj", objects[0].outVert, objects[0].outNorm, objects[0].outUV);

    //Reading and import image and place in initOpenGLProgram
    //Reading into CPU memory
    //Read texture image
    unsigned error0 = lodepng::decode(image0, width0, height0, "wood.png");
    unsigned error1 = lodepng::decode(image1, width1, height1, "brick.png");
    unsigned error2 = lodepng::decode(image2, width2, height2, "niebieski.png");
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
	M = mat4(1.0f);
	//M = rotate(M, -1.0f, r);
	M = translate(M, t);
	M = scale(M, s);
	return M;
}

void SceneBuilder::InProgress(mat4 V)
{
    TextureTryToDo(tex, image0, width0, height0);
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

	//labirynt
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
    TextureTryToDo(tex, image2, width2, height2);
	// floor
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.1f,  0.0f), vec3(8.0f, 0.0f, 6.0f))));
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);

    TextureTryToDo(tex, image1, width1, height1);
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

    glDeleteTextures(1, &tex);
}


void SceneBuilder::TextureTryToDo(GLuint tex, std::vector<unsigned char> image, unsigned width, unsigned height) {
    //Import image into memory associated with the handle
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glEnable(GL_TEXTURE_2D);

}
