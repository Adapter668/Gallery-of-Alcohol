#include "SceneBuilder.h"

SceneBuilder::SceneBuilder()
{
}


SceneBuilder::~SceneBuilder()
{
}

void SceneBuilder::LoadModels()
{
	//mesh1.LoadMesh("BottleOfWine2.obj", outVert1, outNorm1, outUV1);
	//mesh2.LoadMesh("BottleOfWine2.obj", outVert2, outNorm2, outUV2);
	mesh3.LoadMesh("cube.obj", outVert3, outNorm3, outUV3);
	mesh4.LoadMesh("cube.obj", outVert4, outNorm4, outUV4);
	mesh5.LoadMesh("cube.obj", outVert5, outNorm5, outUV5);
	mesh6.LoadMesh("cube.obj", outVert6, outNorm6, outUV6);
	mesh7.LoadMesh("cube.obj", outVert7, outNorm7, outUV7);
	mesh8.LoadMesh("cube.obj", outVert8, outNorm8, outUV8);
	mesh9.LoadMesh("cube.obj", outVert9, outNorm9, outUV9);
	mesh10.LoadMesh("cube.obj", outVert10, outNorm10, outUV10);
	mesh11.LoadMesh("cube.obj", outVert11, outNorm11, outUV11);
	mesh12.LoadMesh("cube.obj", outVert12, outNorm12, outUV12);
	mesh13.LoadMesh("cube.obj", outVert13, outNorm13, outUV13);
	mesh14.LoadMesh("cube.obj", outVert14, outNorm14, outUV14);
	mesh15.LoadMesh("cube.obj", outVert15, outNorm15, outUV15);
	mesh16.LoadMesh("cube.obj", outVert16, outNorm16, outUV16);
	//s³upki
	mesh17a.LoadMesh("cube.obj", outVert17a, outNorm17a, outUV17a);
	mesh17b.LoadMesh("cube.obj", outVert17b, outNorm17b, outUV17b);
	mesh17c.LoadMesh("cube.obj", outVert17c, outNorm17c, outUV17c);
	mesh17d.LoadMesh("cube.obj", outVert17d, outNorm17d, outUV17d);
	mesh17e.LoadMesh("cube.obj", outVert17e, outNorm17e, outUV17e);
	mesh17f.LoadMesh("cube.obj", outVert17f, outNorm17f, outUV17f);
	mesh17g.LoadMesh("cube.obj", outVert17g, outNorm17g, outUV17g);
	mesh17h.LoadMesh("cube.obj", outVert17h, outNorm17h, outUV17h);
	mesh17i.LoadMesh("cube.obj", outVert17i, outNorm17i, outUV17i);
	mesh17j.LoadMesh("cube.obj", outVert17j, outNorm17j, outUV17j);
	mesh17k.LoadMesh("cube.obj", outVert17k, outNorm17k, outUV17k);
	mesh17l.LoadMesh("cube.obj", outVert17l, outNorm17l, outUV17l);
	mesh17m.LoadMesh("cube.obj", outVert17m, outNorm17m, outUV17m);
	mesh17n.LoadMesh("cube.obj", outVert17n, outNorm17n, outUV17n);
	mesh17o.LoadMesh("cube.obj", outVert17o, outNorm17o, outUV17o);
	mesh17p.LoadMesh("cube.obj", outVert17p, outNorm17p, outUV17p);
	//"labirynt"
	mesh18a.LoadMesh("cube.obj", outVert18a, outNorm18a, outUV18a);
	mesh18b.LoadMesh("cube.obj", outVert18b, outNorm18b, outUV18b);
	mesh18c.LoadMesh("cube.obj", outVert18c, outNorm18c, outUV18c);
	mesh18d.LoadMesh("cube.obj", outVert18d, outNorm18d, outUV18d);
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
	/*glLoadMatrixf(value_ptr(V*Adjust(M1, vec3(1.0f, 0.0f, 0.0f), vec3(-6.0f, 0.0f, 2.0f), vec3(0.05f, 0.05f, 0.05f))));
	DrawObject(outVert1, outNorm1, outUV1);
	glLoadMatrixf(value_ptr(V*Adjust(M2, vec3(1.0f, 0.0f, 0.0f), vec3(-5.0f, 0.0f, 2.0f), vec3(0.05f, 0.05f, 0.05f))));
	DrawObject(outVert2, outNorm2, outUV2);*/
	glLoadMatrixf(value_ptr(V*Adjust(M3, vec3(1.0f, 0.0f, 0.0f), vec3(-3.0f, 0.5f, 5.5f), vec3(2.0f, 0.5f, 0.5f))));
	DrawObject(outVert3, outNorm3, outUV3);
	glLoadMatrixf(value_ptr(V*Adjust(M4, vec3(1.0f, 0.0f, 0.0f), vec3(-1.5f, 0.5f, 4.5f), vec3(0.5f, 0.5f, 1.0f))));
	DrawObject(outVert4, outNorm4, outUV4);
	glLoadMatrixf(value_ptr(V*Adjust(M5, vec3(1.0f, 0.0f, 0.0f), vec3(-6.0f, 0.7f, 3.0f), vec3(0.3f, 0.7f, 0.3f))));
	DrawObject(outVert5, outNorm5, outUV5);
	glLoadMatrixf(value_ptr(V*Adjust(M6, vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 1.5f, 5.6f), vec3(1.0f, 0.05f, 0.2f))));
	DrawObject(outVert6, outNorm6, outUV6);
	glLoadMatrixf(value_ptr(V*Adjust(M7, vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 0.7f, 5.6f), vec3(1.0f, 0.05f, 0.2f))));
	DrawObject(outVert7, outNorm7, outUV7);
	glLoadMatrixf(value_ptr(V*Adjust(M8, vec3(1.0f, 0.0f, 0.0f), vec3(-6.0f, 1.5f, 0.2f), vec3(2.0f, 0.05f, 0.2f))));
	DrawObject(outVert8, outNorm8, outUV8);
	glLoadMatrixf(value_ptr(V*Adjust(M9, vec3(1.0f, 0.0f, 0.0f), vec3(-6.0f, 0.7f, 0.2f), vec3(2.0f, 0.05f, 0.2f))));
	DrawObject(outVert9, outNorm9, outUV9);
	glLoadMatrixf(value_ptr(V*Adjust(M10, vec3(1.0f, 0.0f, 0.0f), vec3(-0.5f, 1.5f, -3.0f), vec3(0.2f, 0.05f, 3.0f))));
	DrawObject(outVert10, outNorm10, outUV10);
	glLoadMatrixf(value_ptr(V*Adjust(M11, vec3(1.0f, 0.0f, 0.0f), vec3(-0.5f, 0.5f, -3.0f), vec3(0.2f, 0.05f, 3.0f))));
	DrawObject(outVert11, outNorm11, outUV11);
	glLoadMatrixf(value_ptr(V*Adjust(M12, vec3(1.0f, 0.0f, 0.0f), vec3(-2.0f, 0.7f, -4.0f), vec3(0.5f, 0.7f, 0.5f))));
	DrawObject(outVert12, outNorm12, outUV12);
	glLoadMatrixf(value_ptr(V*Adjust(M13, vec3(1.0f, 0.0f, 0.0f), vec3(-2.0f, 0.7f, -2.0f), vec3(0.5f, 0.7f, 0.5f))));
	DrawObject(outVert13, outNorm13, outUV13);
	glLoadMatrixf(value_ptr(V*Adjust(M14, vec3(1.0f, 0.0f, 0.0f), vec3(-4.5f, 0.7f, -4.0f), vec3(0.5f, 0.7f, 0.5f))));
	DrawObject(outVert14, outNorm14, outUV14);
	glLoadMatrixf(value_ptr(V*Adjust(M15, vec3(1.0f, 0.0f, 0.0f), vec3(-4.5f, 0.7f, -2.0f), vec3(0.5f, 0.7f, 0.5f))));
	DrawObject(outVert15, outNorm15, outUV15);
	glLoadMatrixf(value_ptr(V*Adjust(M16, vec3(1.0f, 0.0f, 0.0f), vec3(-6.5f, 0.7f, -4.0f), vec3(0.2f, 0.7f, 2.0f))));
	DrawObject(outVert16, outNorm16, outUV16);
	

	glLoadMatrixf(value_ptr(V*Adjust(M17a, vec3(1.0f, 0.0f, 0.0f), vec3(4.0f, 0.5f, 3.5f), vec3(0.1f, 0.5f, 0.1f))));
	DrawObject(outVert17a, outNorm17a, outUV17a);
	glLoadMatrixf(value_ptr(V*Adjust(M17b, vec3(1.0f, 0.0f, 0.0f), vec3(4.0f, 0.7f, 5.0f), vec3(0.1f, 0.7f, 0.1f))));
	DrawObject(outVert17b, outNorm17b, outUV17b);
	glLoadMatrixf(value_ptr(V*Adjust(M17c, vec3(1.0f, 0.0f, 0.0f), vec3(5.0f, 0.7f, 3.5f), vec3(0.1f, 0.7f, 0.1f))));
	DrawObject(outVert17c, outNorm17c, outUV17c);
	glLoadMatrixf(value_ptr(V*Adjust(M17d, vec3(1.0f, 0.0f, 0.0f), vec3(5.0f, 0.5f, 5.0f), vec3(0.1f, 0.5f, 0.1f))));
	DrawObject(outVert17d, outNorm17d, outUV17d);
	glLoadMatrixf(value_ptr(V*Adjust(M17e, vec3(1.0f, 0.0f, 0.0f), vec3(6.0f, 0.5f, 3.5f), vec3(0.1f, 0.5f, 0.1f))));
	DrawObject(outVert17e, outNorm17e, outUV17e);
	glLoadMatrixf(value_ptr(V*Adjust(M17f, vec3(1.0f, 0.0f, 0.0f), vec3(6.0f, 0.7f, 5.0f), vec3(0.1f, 0.7f, 0.1f))));
	DrawObject(outVert17f, outNorm17f, outUV17f);
	glLoadMatrixf(value_ptr(V*Adjust(M17g, vec3(1.0f, 0.0f, 0.0f), vec3(7.0f, 0.7f, 3.5f), vec3(0.1f, 0.7f, 0.1f))));
	DrawObject(outVert17g, outNorm17g, outUV17g);
	glLoadMatrixf(value_ptr(V*Adjust(M17h, vec3(1.0f, 0.0f, 0.0f), vec3(7.0f, 0.5f, 5.0f), vec3(0.1f, 0.5f, 0.1f))));
	DrawObject(outVert17h, outNorm17h, outUV17h);
	glLoadMatrixf(value_ptr(V*Adjust(M17i, vec3(1.0f, 0.0f, 0.0f), vec3(3.5f, 0.5f, 2.7f), vec3(0.1f, 0.5f, 0.1f))));
	DrawObject(outVert17i, outNorm17i, outUV17i);
	glLoadMatrixf(value_ptr(V*Adjust(M17j, vec3(1.0f, 0.0f, 0.0f), vec3(3.5f, 0.7f, 4.3f), vec3(0.1f, 0.7f, 0.1f))));
	DrawObject(outVert17j, outNorm17j, outUV17j);
	glLoadMatrixf(value_ptr(V*Adjust(M17k, vec3(1.0f, 0.0f, 0.0f), vec3(4.5f, 0.7f, 2.7f), vec3(0.1f, 0.7f, 0.1f))));
	DrawObject(outVert17k, outNorm17k, outUV17k);
	glLoadMatrixf(value_ptr(V*Adjust(M17l, vec3(1.0f, 0.0f, 0.0f), vec3(4.5f, 0.5f, 4.3f), vec3(0.1f, 0.5f, 0.1f))));
	DrawObject(outVert17l, outNorm17l, outUV17l);
	glLoadMatrixf(value_ptr(V*Adjust(M17m, vec3(1.0f, 0.0f, 0.0f), vec3(5.5f, 0.5f, 2.7f), vec3(0.1f, 0.5f, 0.1f))));
	DrawObject(outVert17m, outNorm17m, outUV17m);
	glLoadMatrixf(value_ptr(V*Adjust(M17n, vec3(1.0f, 0.0f, 0.0f), vec3(5.5f, 0.7f, 4.3f), vec3(0.1f, 0.7f, 0.1f))));
	DrawObject(outVert17n, outNorm17n, outUV17n);
	glLoadMatrixf(value_ptr(V*Adjust(M17o, vec3(1.0f, 0.0f, 0.0f), vec3(6.5f, 0.7f, 2.7f), vec3(0.1f, 0.7f, 0.1f))));
	DrawObject(outVert17o, outNorm17o, outUV17o);
	glLoadMatrixf(value_ptr(V*Adjust(M17p, vec3(1.0f, 0.0f, 0.0f), vec3(6.5f, 0.5f, 4.3f), vec3(0.1f, 0.5f, 0.1f))));
	DrawObject(outVert17p, outNorm17p, outUV17p);

	glLoadMatrixf(value_ptr(V*Adjust(M18a, vec3(1.0f, 0.0f, 0.0f), vec3(4.0f, 0.7f, -1.5f), vec3(2.5f, 0.7f, 0.2f))));
	DrawObject(outVert18a, outNorm18a, outUV18a);
	glLoadMatrixf(value_ptr(V*Adjust(M18b, vec3(1.0f, 0.0f, 0.0f), vec3(1.5f, 0.7f, -3.0f), vec3(0.2f, 0.7f, 1.7f))));
	DrawObject(outVert18b, outNorm18b, outUV18b);
	glLoadMatrixf(value_ptr(V*Adjust(M18c, vec3(1.0f, 0.0f, 0.0f), vec3(3.5f, 0.7f, -4.5f), vec3(2.0f, 0.7f, 0.2f))));
	DrawObject(outVert18c, outNorm18c, outUV18c);
	glLoadMatrixf(value_ptr(V*Adjust(M18d, vec3(1.0f, 0.0f, 0.0f), vec3(5.5f, 0.7f, -3.0f), vec3(2.5f, 0.7f, 0.2f))));
	DrawObject(outVert18d, outNorm18d, outUV18d);
}
