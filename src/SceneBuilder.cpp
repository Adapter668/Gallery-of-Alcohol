#include "SceneBuilder.h"
#include "lodepng.h"
#include "special_effects.h"

vector<cuboid> SceneBuilder::all_models_coordinates;

void SceneBuilder::LoadModelsToMemory()
{
	objects[CUBE].mesh.LoadMesh("cube.obj", objects[0].outVert, objects[0].outNorm, objects[0].outUV);

    //Reading and import image and place in initOpenGLProgram
    //Reading into CPU memory
    //Read texture image
    unsigned error0 = lodepng::decode(image0, width0, height0, "wood.png");     // furniture
    unsigned error1 = lodepng::decode(image1, width1, height1, "beige.png");       // walls
    unsigned error2 = lodepng::decode(image2, width2, height2, "czerwony2.png");    // floor
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
    GLfloat mat_emission[] = {0.3, 0.2, 0.2, 0.0};
    GLfloat no_emission[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat no_specular[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat low_shininess[] = { 5.0 };
    GLfloat no_shininess[] = {0.0};

    ApplyTexture(tex, image0, width0, height0);
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

//    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);      // light emission
//    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//    glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
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

//    glMaterialfv(GL_FRONT, GL_SPECULAR, no_specular);
//    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
//    glMaterialfv(GL_FRONT, GL_EMISSION, no_emission);   // end of light emission

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
    ApplyTexture(tex, image2, width2, height2);
	// floor
	glLoadMatrixf(value_ptr(V*Adjust(objects[0].M, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f,  0.0f), vec3(8.0f, 0.0f, 6.0f))));
	DrawObject(objects[0].outVert, objects[0].outNorm, objects[0].outUV);

    ApplyTexture(tex, image1, width1, height1);
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


void SceneBuilder::ApplyTexture(GLuint tex, std::vector<unsigned char> image, unsigned width, unsigned height) {
    //Import image into memory associated with the handle
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glEnable(GL_TEXTURE_2D);

}

void SceneBuilder::getObjectsOuts(short type, vector<float> &outVert, vector<float> &outNorm, vector<float> &outUV) {
    outVert = objects[type].outVert;
    outNorm = objects[type].outNorm;
    outUV = objects[type].outUV;
}