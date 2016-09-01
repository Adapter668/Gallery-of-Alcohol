#pragma once
#include <glm/glm.hpp>
#include <stdbool.h>

#include "SceneBuilder.h"

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
	glm::vec3* getCamerasPosition() { return &position; };
	void directionUpdate(short direction);
	void positionUpdate(short way);
    void loadMatrices();

    // alkohol effects:
    void different_perspective(float aspect);
    void upsideDown();
    void closePerspective(float angle);

private:
	bool checkIfPossibleToMove(glm::vec3 newPosition);		// collision detection
};