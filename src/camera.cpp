#include "camera.h"
#include "constants.h"
#include <glm/gtx/transform.hpp>


Camera::Camera() :
        //position(0.0f, 1.0f, 0.0f),
        position(1.0f, 1.0f, 0.8f),
        viewDirection(0.0f, 0.0f, 2.0f),
        UP(0.0f, 1.0f, 0.0f)
//        position(0.0f, 5.0f, 0.0f),
//        viewDirection(0.0f, -2.5f, 2.0f),
//        UP(0.0f, 1.0f, 0.0f)
{
}

glm::mat4 Camera::getWorldToViewMatrix() const {
	return lookAt(position, position + viewDirection, UP);
}

void Camera::directionUpdate(short direction) {
	if (direction == LEFT) {
		viewDirection = glm::mat3(glm::rotate(SPEED_OF_ROTATE, UP)) * viewDirection;
	}
	if (direction == RIGHT) {
		viewDirection = glm::mat3(glm::rotate(-SPEED_OF_ROTATE, UP)) * viewDirection;
	}
}

void Camera::positionUpdate(short way) {
    glm::vec3 newPosition =position;
    if (way == FORWARD) {
        newPosition = position + viewDirection*SPEED_OF_ROTATE;
    }
    if (way == BACK) {
        newPosition = position - viewDirection*SPEED_OF_ROTATE;
    }
    if (!checkIfPossibleToMove(newPosition)) return;  // collision detection
   position = newPosition;
}

void Camera::mouseUpdate(const glm::vec2& newMousePosition) {
	glm::vec2 lookDelta = newMousePosition - oldMousePosition;
	viewDirection = glm::mat3(glm::rotate(lookDelta.x, UP)) * viewDirection;
	oldMousePosition = newMousePosition;
}

bool collisionDetected(glm::vec3 newPosition, cuboid object) {
    if (    (newPosition.x >= object.front_2.x and newPosition.x <= object.front_1.x) and
            (newPosition.z >= object.front_2.z and newPosition.z <= object.back_2.z) and
            newPosition.y >= object.front_3.y and newPosition.y <= object.front_2.y) {
        return true;        // collision detected
    }
    else return false;  // there is no collision detected
}

bool Camera::checkIfPossibleToMove(glm::vec3 newPosition) {
    // TODO detecting collision
    for (auto object: SceneBuilder::all_models_coordinates) {
        if (collisionDetected(newPosition, object)) return false;   // it's not possible to move
    }
    return true;        // it is possible to move
}

//bool Camera::checkIfPossibleToMove(vec3 newPosition, SceneBuilder* sceneBuilder) {
//    for ( auto object : sceneBuilder->all_models_coordinates) {
//        if (newPosition.x < object.back_1.x and
//                newPosition.x > object.back_2.x and
//                newPosition.z < object.back_1.z and
//                newPosition.z > object.front_1.z) return false;
//    }
//	return true;
//}