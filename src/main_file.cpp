#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stdio.h>
#include <iostream>
#include <vector>
#include <libltdl/lt_system.h>
#include <stdlib.h>

#include "constants.h"
#include "sceneBuilder.h"
#include "camera.h"
#include "special_effects.h"

using namespace glm;
using namespace std;

GLFWwindow*  main_window;				// Pointer to object that represents the application window
Camera              camera;					// Camera's declaration
SceneBuilder     sceneBuilder;
Special_effects  special_effects(&camera, &sceneBuilder);
short                    directionToLook = NONE;	// Helps moving camera
short                     positionToGo = NONE;		// Helps moving camera

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

void mouse_click_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        int window_width, window_height, chosen_bottle;
        double mouse_x, mouse_y;
        glfwGetWindowSize(window, &window_width, &window_height);
        glfwGetCursorPos(window, &mouse_x, &mouse_y);
        chosen_bottle = camera.mousePicking(mouse_x, mouse_y, window_width, window_height);
        if (chosen_bottle != NO_BOTTLE_COLLISION) {
            special_effects.bottleDetected(chosen_bottle);
        }
    }
}

// INITIALIZATION CODE PROCEDURE
void initOpenGLProgram(GLFWwindow* window) {
	//glBufferData(GL_ARRAY_BUFFER, outVert.size() * sizeof(glm::vec3), &outVert[0], GL_STATIC_DRAW);
    sceneBuilder.LoadModelsToMemory();	                // loading another models (cube)
	//************Place any code here that needs to be executed once, at the program start************
	glClearColor(0, 0, 0, 0);                      // Clear background with black color
	glEnable(GL_LIGHTING);                     // Turn on lighting mode
	glEnable(GL_LIGHT0);                           //Turn on default light 0
	glEnable(GL_DEPTH_TEST);                //Turn on hidden surface removal via depth buffer
	glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

	glfwSetErrorCallback(error_callback);	//Register error processing callback procedure
	glfwSetKeyCallback(window, key_callback); //register the key_callback procedure
	glfwSetMouseButtonCallback(window, mouse_click_callback); // register the mouse callback procedure
}


// DRAWING SCENE
void drawScene(GLFWwindow* window) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera.loadMatrices();      // load matrices of camera
    camera.lights();                    // lights
    sceneBuilder.BuildScene(camera.getWorldToViewMatrix());        //glLoad, draw
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
    main_window = glfwCreateWindow(800, 600, "Alcohol Gallery", NULL, NULL);
    if (!main_window) {			//If no window is opened then close the program
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(main_window); //Since this moment OpenGL context corresponding to the window is active and all OpenGL calls will refer to this context.
	glfwSwapInterval(1); //During vsync wait for the first refresh
	GLenum err;
	if ((err = glewInit()) != GLEW_OK) { //Initialize GLEW library
		fprintf(stderr, "Can't initialize GLEW: %s\n", glewGetErrorString(err));
		exit(EXIT_FAILURE);
	}
	initOpenGLProgram(main_window); //Call initialization procedure

	//**********MAIN APPLICATION LOOP: **************
	while (!glfwWindowShouldClose(main_window)) { //As long as the window shouldnt be closed yet...
        camera.directionUpdate(directionToLook);	// change direction of camera (LEFT, RIGHT)
		camera.positionUpdate(positionToGo);		// change position of camera (FORWARD, BACK)
		drawScene(main_window);							//Execute drawing procedure
		glfwPollEvents();							//Process callback procedures corresponding to the events that took place up to now
	}

	glfwDestroyWindow(main_window);			//Delete OpenGL context and the window.
	glfwTerminate();					//Free GLFW resources
	exit(EXIT_SUCCESS);
}