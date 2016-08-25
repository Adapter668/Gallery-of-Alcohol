#pragma once
#include <glm/glm.hpp>
#include <stdbool.h>

#include "SceneBuilder.h"

class Camera {
	glm::vec3 position;
	glm::vec3 viewDirection;
	const glm::vec3 UP;
	glm::vec2 oldMousePosition;								// TODO
	
public:
	Camera();
	glm::mat4 getWorldToViewMatrix() const;
	glm::vec3* getCamerasPosition() { return &position; };
	void directionUpdate(short direction);
	void positionUpdate(short way);
	void mouseUpdate(const glm::vec2& newMousePosition);	// TODO

private:
	bool checkIfPossibleToMove(glm::vec3 newPosition);		// collision detection
};