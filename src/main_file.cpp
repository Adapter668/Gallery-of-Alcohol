#define GLM_FORCE_RADIANS


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
#include "lodepng.h"
#include "MeshLoader.h"
#include "SceneBuilder.h"
#include "camera.h"

using namespace glm;
using namespace std;


GLFWwindow* window;				// Pointer to object that represents the application window
Camera camera;					// Camera's declaration
short directionToLook = NONE;	// Helps moving camera
short positionToGo = NONE;		// Helps moving camera

//---RUBISH---
mat4 projectionMatrix;
mat4 roomModel;
GLuint tex; 

SceneBuilder sceneBuilder; 
MeshLoader roomMesh;
vector<float>outVert;
vector<float>outNorm;
vector<float>outUv;
//------------

// CALLBACK PROCEDURES:
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mod) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_ESCAPE) {
			glfwDestroyWindow(window);
			glfwTerminate();
			exit(EXIT_SUCCESS);
		}
		if (key == GLFW_KEY_A || key == GLFW_KEY_LEFT) {
			directionToLook = LEFT;
		}
		if (key == GLFW_KEY_D || key == GLFW_KEY_RIGHT) {
			directionToLook = RIGHT;
		}
		if (key == GLFW_KEY_W || key == GLFW_KEY_UP) {
			positionToGo = FORWARD;
		}
		if (key == GLFW_KEY_S || key == GLFW_KEY_DOWN) {
			positionToGo = BACK;
		}
	}
	if (action == GLFW_RELEASE) { //If the user released a key, zero the appropriate angular speed
		if (key == GLFW_KEY_W || key == GLFW_KEY_S || key == GLFW_KEY_UP || key == GLFW_KEY_DOWN) positionToGo = NONE;
		if (key == GLFW_KEY_A || key == GLFW_KEY_D || key == GLFW_KEY_LEFT || key == GLFW_KEY_RIGHT) directionToLook = NONE;
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		// TODO choose buttle to drink
	}	
}

void cursor_callback(GLFWwindow *window, double x, double y) {
	// TODO changing direction using mouse
}

// INITIALIZATION CODE PROCEDURE
void initOpenGLProgram(GLFWwindow* window) {
	//roomMesh.LoadMesh("room with tekxture.obj", outVert, outNorm, outUv);
	glBufferData(GL_ARRAY_BUFFER, outVert.size() * sizeof(glm::vec3), &outVert[0], GL_STATIC_DRAW);
	
	sceneBuilder.LoadModels();	                // loading another models (cube)
	//************Place any code here that needs to be executed once, at the program start************
	glClearColor(0, 30, 0, 1);                      // Clear background with black color
	glEnable(GL_LIGHTING);                     // Turn on lighting mode
	glEnable(GL_LIGHT0);                           //Turn on default light 0
	glEnable(GL_DEPTH_TEST);                //Turn on hidden surface removal via depth buffer
	glEnable(GL_NORMALIZE);

	glfwSetErrorCallback(error_callback);	//Register error processing callback procedure
	glfwSetKeyCallback(window, key_callback); //register the key_callback procedure
	glfwSetCursorPosCallback(window, cursor_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback); // register the mouse callback procedure

    /*
	//----------------------------------------------------------------------------------------------------
	//Reading and import image � place in initOpenGLProgram
	//Reading into CPU memory
	std::vector<unsigned char> image; //Allocate a vector for image data
	unsigned width, height; //Variables for image size
	//Read texture image
	unsigned error = lodepng::decode(image, width, height, "bricks.png");
	//Import into graphics card memory
	glGenTextures(1, &tex); //Initialize one handle
	glBindTexture(GL_TEXTURE_2D, tex); //Activate handle
	//Import image into memory associated with the handle
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glEnable(GL_TEXTURE_2D);
    */

	//----------------------------------------------------------------------------------------------------
}

//------Drawing procedure------
void drawScene(GLFWwindow* window) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//****************CAMERA AND VIEW************************************
	projectionMatrix = perspective(50.0f*PI / 180.0f, 1.0f, 1.0f, 50.0f);// Compute projection matrix
	roomModel = mat4(1.0f); //Compute model matrix of room
	
	//Load matrices into OpenGL
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(value_ptr(projectionMatrix));								// P
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(value_ptr(camera.getWorldToViewMatrix()));				// V
	glLoadMatrixf(value_ptr(camera.getWorldToViewMatrix() * roomModel));	// V*M

	// LIGHT:
	// main light:
	float lightPos[] = { 0,0,0,0 };					//if w=0 -> direction of light
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	// light from camera:
	lightPos[0] = camera.getCamerasPosition()->x;
	lightPos[1] = camera.getCamerasPosition()->y;
	lightPos[2] = camera.getCamerasPosition()->z;
	lightPos[3] = 1;								// if w=1 -> location of light
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	
	//**************CAMERAs END****************************************

	// DRAWING CODE:
	glEnableClientState(GL_VERTEX_ARRAY); //Tell OpenGL to use vertex coordinate array for drawing
	//glEnableClientState(GL_COLOR_ARRAY); //Tell OpenGL to use color array for drawing
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, outVert.data());						 
	glNormalPointer(GL_FLOAT, 0, outNorm.data());
	glTexCoordPointer(2, GL_FLOAT, 0, outUv.data());
	glDrawArrays(GL_TRIANGLES, 0, outVert.size() / 3); // Draw

	glDisableClientState(GL_VERTEX_ARRAY); //Tell OpenGL to not use vertex coordinate array for drawing anymore
	//glDisableClientState(GL_COLOR_ARRAY); //Tell OpenGL to not use color array for drawing anymore
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	//-------------------------------------------------------
	
	sceneBuilder.InProgress(camera.getWorldToViewMatrix());		//glLoad, draw
	glfwSwapBuffers(window);				//Copy back buffer into front buffer
}

int main(void) {
	if (!glfwInit()) { //Initialize GLFW library
		fprintf(stderr, "Can't initialize GLFW.\n");
		exit(EXIT_FAILURE);
	}
	GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);
	//window = glfwCreateWindow(mode->width, mode->height, "Alcohol Gallery", primaryMonitor, NULL);  //Create a window 500pxx500px titled "OpenGL" and an OpenGL context associated with it.
    window = glfwCreateWindow(800, 600, "Alcohol Gallery", NULL, NULL);
    if (!window) {			//If no window is opened then close the program
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window); //Since this moment OpenGL context corresponding to the window is active and all OpenGL calls will refer to this context.
	glfwSwapInterval(1); //During vsync wait for the first refresh
	GLenum err;
	if ((err = glewInit()) != GLEW_OK) { //Initialize GLEW library
		fprintf(stderr, "Can't initialize GLEW: %s\n", glewGetErrorString(err));
		exit(EXIT_FAILURE);
	}
	initOpenGLProgram(window); //Call initialization procedure

	//**********MAIN APPLICATION LOOP: **************
	while (!glfwWindowShouldClose(window)) { //As long as the window shouldnt be closed yet...
		camera.directionUpdate(directionToLook);	// change direction of camera (LEFT, RIGHT)
		camera.positionUpdate(positionToGo);		// change position of camera (FORWARD, BACK)
		drawScene(window);							//Execute drawing procedure
		glfwPollEvents();							//Process callback procedures corresponding to the events that took place up to now
	}

	//**********DELETING TEXTURES: ******************
	glDeleteTextures(1, &tex);

	glfwDestroyWindow(window);			//Delete OpenGL context and the window.
	glfwTerminate();					//Free GLFW resources
	exit(EXIT_SUCCESS);
}