#include "camera.h"
#include "constants.h"
#include <glm/gtx/transform.hpp>


Camera::Camera() :
        //position(0.0f, 1.0f, 0.0f),
        position(1.0f, 1.0f, 0.8f),
        viewDirection(0.0f, 0.0f, 2.0f),
        UP(0.0f, 1.0f, 0.0f)
// upper perspective
//        position(0.0f, 5.0f, 0.0f),
//        viewDirection(0.0f, -2.5f, 2.0f),
//        UP(0.0f, 1.0f, 0.0f)
{ }

glm::mat4 Camera::getWorldToViewMatrix() const {
	return lookAt(position, position + viewDirection, UP);
}

void Camera::directionUpdate(short direction) {
    glm::vec3 newDirectionToDetectCollision = viewDirection;
	if (direction == LEFT) {
		viewDirection = glm::mat3(glm::rotate(SPEED_OF_ROTATE, UP)) * viewDirection;
	}
	if (direction == RIGHT) {
		viewDirection = glm::mat3(glm::rotate(-SPEED_OF_ROTATE, UP)) * viewDirection;
	}
}

void Camera::loadMatrices() {
    mat4 projectionMatrix;
    mat4 modelMatrix;
    projectionMatrix = perspective(50.0f*PI / 180.0f, 1.0f, 1.0f, 50.0f);// Compute projection matrix
    modelMatrix = mat4(1.0f); //Compute model matrix of room

    //Load matrices into OpenGL
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(value_ptr(projectionMatrix));								// P
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(value_ptr(this->getWorldToViewMatrix()));				// V
    glLoadMatrixf(value_ptr(this->getWorldToViewMatrix() * modelMatrix));	// V*M

}

void Camera::positionUpdate(short way) {
    glm::vec3 newPositionToDetectCollision =position;
    glm::vec3 newPositionToGo = position;
    if (way == FORWARD) {
        newPositionToDetectCollision = position + viewDirection * DISTANCE_IN_COLLISION *SPEED_OF_ROTATE;
        newPositionToGo = position + viewDirection *SPEED_OF_ROTATE;
    }
    if (way == BACK) {
        newPositionToDetectCollision = position - viewDirection* DISTANCE_IN_COLLISION * SPEED_OF_ROTATE;
        newPositionToGo = position - viewDirection *SPEED_OF_ROTATE;
    }
    if (!checkIfPossibleToMove(newPositionToDetectCollision)) return;  // collision detection
   position = newPositionToGo;
}

void Camera::mouseUpdate(const glm::vec2& newMousePosition) {
	glm::vec2 lookDelta = newMousePosition - oldMousePosition;
	viewDirection = glm::mat3(glm::rotate(lookDelta.x, UP)) * viewDirection;
	oldMousePosition = newMousePosition;
}

bool collisionDetected(glm::vec3 newPosition, cuboid object) {
    if (    (newPosition.x >= object.front_2.x and newPosition.x <= object.front_1.x) and
            (newPosition.z >= object.front_2.z and newPosition.z <= object.back_2.z)  and
            ((newPosition.y-0.6f) >= object.front_3.y  and (newPosition.y-0.6f) <= object.front_2.y) ) {
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