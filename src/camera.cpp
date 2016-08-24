#include "camera.h"
#include "constants.h"
#include <glm/gtx/transform.hpp>


Camera::Camera() :
        position(0.0f, 1.0f, 0.0f),
        viewDirection(0.0f, 0.0f, 2.0f),
        UP(0.0f, 1.0f, 0.0f)
//position(0.0f, 5.0f, 0.0f),
//viewDirection(0.0f, -2.5f, 2.0f),
//UP(0.0f, 1.0f, 0.0f)
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
    if (checkIfPossibleToMove() == false) return;
    if (way == FORWARD) {
        position = position + viewDirection*SPEED_OF_ROTATE;
    }
    if (way == BACK) {
        position = position - viewDirection*SPEED_OF_ROTATE;
    }
}

void Camera::mouseUpdate(const glm::vec2& newMousePosition) {
	glm::vec2 lookDelta = newMousePosition - oldMousePosition;
	viewDirection = glm::mat3(glm::rotate(lookDelta.x, UP)) * viewDirection;
	oldMousePosition = newMousePosition;
}

bool Camera::checkIfPossibleToMove() {
    // TODO detecting collision
    return true;
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