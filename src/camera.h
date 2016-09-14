#pragma once
#include <glm/glm.hpp>
#include <stdbool.h>

#include "sceneBuilder.h"

class Camera {
    glm::vec3 position;
    glm::vec3 viewDirection;
    glm::vec3 UP;
    mat4 projectionMatrix;

public:
    short                    directionToLook = NONE;	// Helps moving camera
    short                     positionToGo = NONE;		// Helps moving camera
    bool collision_on = true;
    bool upside_down = false;
    bool common_perspective = true;
    bool close = false;

	Camera();
	glm::mat4 getWorldToViewMatrix() const;
	glm::vec3 getCamerasPosition() { return position; };
    glm::vec3 getCamerasViewDirection() { return viewDirection; };
	void directionUpdate();
	void positionUpdate();
    void loadMatrices();
    void lights();
    int mousePicking(double mouse_x, double mouse_y, int window_width, int window_height);

    // alkohol effects:
    void different_perspective(float aspect);
    void upsideDown();
    void closePerspective(float angle);
    void differentColors();

private:
	bool checkIfPossibleToMove(glm::vec3 newPosition);		// collision detection
    void mainLight();

};