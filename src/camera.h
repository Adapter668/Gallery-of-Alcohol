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
    bool collision_on = true;
    bool upside_down = false;
    bool common_perspective = true;
    bool close = false;

	Camera();
	glm::mat4 getWorldToViewMatrix() const;
	glm::vec3 getCamerasPosition() { return position; };
    glm::vec3 getCamerasViewDirection() { return viewDirection; };
	void directionUpdate(short direction);
	void positionUpdate(short way);
    void loadMatrices();
    void lights();

    // alkohol effects:
    void different_perspective(float aspect);
    void upsideDown();
    void closePerspective(float angle);
    void differentColors();

private:
	bool checkIfPossibleToMove(glm::vec3 newPosition);		// collision detection

};