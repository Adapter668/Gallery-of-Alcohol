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
{
    projectionMatrix = perspective(50.0f*PI / 180.0f, 1.0f, 1.0f, 50.0f);
}

glm::mat4 Camera::getWorldToViewMatrix() const {
	return lookAt(position, position + viewDirection, UP);
}

void Camera::directionUpdate(short direction) {
    glm::vec3 newDirectionToDetectCollision = viewDirection;
    glm::vec3 newPositionToDetectCollision =position;
	if (direction == LEFT) {
        newDirectionToDetectCollision = glm::mat3(glm::rotate(SPEED_OF_ROTATE, UP)) * viewDirection;
        newPositionToDetectCollision = position + newDirectionToDetectCollision * DISTANCE_IN_COLLISION *SPEED_OF_ROTATE;
        if (!checkIfPossibleToMove(newPositionToDetectCollision)) return;
		viewDirection = glm::mat3(glm::rotate(SPEED_OF_ROTATE, UP)) * viewDirection;
	}
	if (direction == RIGHT) {
        newDirectionToDetectCollision = glm::mat3(glm::rotate(-SPEED_OF_ROTATE, UP)) * viewDirection;
        newPositionToDetectCollision = position + newDirectionToDetectCollision * DISTANCE_IN_COLLISION *SPEED_OF_ROTATE;
        if (!checkIfPossibleToMove(newPositionToDetectCollision)) return;
		viewDirection = glm::mat3(glm::rotate(-SPEED_OF_ROTATE, UP)) * viewDirection;
	}
}

void Camera::loadMatrices() {
    mat4 modelMatrix;
    modelMatrix = mat4(1.0f); //Compute model matrix of room

    //Load matrices into OpenGL
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(value_ptr(this->projectionMatrix));								// P
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(value_ptr(this->getWorldToViewMatrix()));				// V
    glLoadMatrixf(value_ptr(this->getWorldToViewMatrix() * modelMatrix));	// V*M
}

void Camera::lights() {
   float lightPos[4];				//if w=0 -> direction of light
    // light in front of camera:
    glm::vec3 newPosition = position;
    newPosition = newPosition + viewDirection * DISTANCE_IN_COLLISION *SPEED_OF_ROTATE;
    lightPos[0] = newPosition.x;
    lightPos[1] = newPosition.y;
    lightPos[2] = newPosition.z;
    lightPos[3] = 1;								// if w=1 -> location of light
    glLightfv(GL_LIGHT0,GL_POSITION, lightPos);

    differentColors();      // color change effect
    mainLight();
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

bool collisionDetected(glm::vec3 newPosition, cuboid object) {
    if (    (newPosition.x >= object.front_2.x and newPosition.x <= object.front_1.x) and
            (newPosition.z >= object.front_2.z and newPosition.z <= object.back_2.z)  and
            ((newPosition.y) >= object.front_3.y  and (object.front_2.y) > 0.3f) ) {
        return true;        // collision detected
    }
    else return false;  // there is no detected collision
}

bool Camera::checkIfPossibleToMove(glm::vec3 newPosition) {
    if (!collision_on) return true;     // if collision turned off -> it's always possible to move
    for (auto object: SceneBuilder::all_cuboid_models_coordinates) {
        if (collisionDetected(newPosition, object)) return false;   // it's not possible to move
    }
    return true;        // it is possible to move
}

void Camera::upsideDown() {
    if (!upside_down) {
        this->UP.y = -1.0f;
        upside_down = true;
        cout << "Upside down on\n";
    }
    else {
        this->UP.y = 1.0f;
        upside_down = false;
        cout << "Upside down off\n";
    }
}

void Camera::different_perspective(float aspect) {
//    if (common_perspective) {
        common_perspective = false;
        projectionMatrix = perspective(50.0f*PI / 180.0f, aspect, 1.0f, 50.0f);
        cout << "Different perspective on\n";
//    }
//    else {
//        common_perspective = true;
//        projectionMatrix = perspective(50.0f*PI / 180.0f, 1.0f, 1.0f, 50.0f);
//        cout << "Different perspective off\n";
//    }
}

void Camera::closePerspective(float angle) {
//   if (!close) {
        close = true;
        projectionMatrix = perspective(angle*PI / 180.0f, 1.0f, 1.0f, 50.0f);
        cout << "Close on\n";
//    }
////   else {
////        close = false;
////        projectionMatrix = perspective(50.0f*PI / 180.0f, 1.0f, 1.0f, 50.0f);
////        cout << "Close off\n";
////    }
}

void Camera::differentColors() {
    float lightPos[4];
    glm::vec3 newPosition = position;
    newPosition = newPosition + viewDirection * DISTANCE_IN_COLLISION *SPEED_OF_ROTATE;
    lightPos[0] = newPosition.x;
    lightPos[1] = newPosition.y;
    lightPos[2] = newPosition.z;
    lightPos[3] = 1;
    glLightfv(GL_LIGHT1,GL_AMBIENT, lightPos);
    glLightfv(GL_LIGHT1,GL_DIFFUSE, lightPos);
    glLightfv(GL_LIGHT1,GL_SPECULAR, lightPos);
}

void Camera::mainLight() {
    glEnable(GL_LIGHT3);
    GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
    GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat position[] = { -1.5f, 3.0f, -4.0f, 1.0f };

    glLightfv(GL_LIGHT3, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT3, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT3, GL_POSITION, position);
}

float angleBetween( glm::vec3 a, glm::vec3 b){
    glm::vec3 da=glm::normalize(a);
    glm::vec3 db=glm::normalize(b);
    return acos(glm::dot(da, db));
}

int Camera::mousePicking(double mouse_x, double mouse_y, int window_width, int window_height) {
    // NORMALISED DEVICE COORDINATES
    // range [-1:1, -1:1, -1:1]
    float x = (2.0f * mouse_x) / window_width - 1.0f;
    float y = 1.0f - (2.0f * mouse_y) / window_height;
    float z = 1.0f;
    glm::vec3 ray_nds = glm::vec3 (x, y, z);

    float my_zet = 1.0;
    // HOMOGENEOUS CLIP COORDINATES
    // range [-1:1, -1:1, -1:1, -1:1]
    //We want our ray's z to point forwards - this is usually the negative z direction in OpenGL style.
    // We can add a w, just so that we have a 4d vector.
    glm::vec4 ray_clip = glm::vec4(ray_nds.x, ray_nds.y,  my_zet, 1.0);     // z = 1 !!

    // CAMERA COORDINATES
    // range [-x:x, -y:y, -z:z, -w:w]
    // Normally, to get into clip space from eye space we multiply the vector by a projection matrix.
    // We can go backwards by multiplying by the inverse of this matrix.
    glm::vec4 ray_eye = inverse (projectionMatrix) * ray_clip;
    ray_eye = glm::vec4 (ray_eye.x, ray_eye.y, -1.0, 0.0);           // z,w -> forwards, and not a point

    // WORLD COORDINATES
    // range [-x:x, -y:y, -z:z, -w:w]
    // Remember that we manually specified a -1 for the z component, which means that our ray isn't normalised.
    // We should do this before we use it.
    glm::vec3 ray_wor;
    ray_wor.x = (inverse (getWorldToViewMatrix()) * ray_eye).x;
    ray_wor.y = (inverse (getWorldToViewMatrix()) * ray_eye).y;
    ray_wor.z = (inverse (getWorldToViewMatrix()) * ray_eye).z;
    // don't forget to normalise the vector at some point
    ray_wor = normalize(ray_wor);
    //This should balance the up-and-down, left-and-right, and forwards components for us.
    // So, assuming our camera is looking directly along the -Z world axis, we should get [0,0,-1]
    // when the mouse is in the centre of the screen, and less significant z values when the mouse moves around the screen.
    // This will depend on the aspect ratio, and field-of-view defined in the view and projection matrices.
    // We now have a ray that we can compare with surfaces in world space.

    int chosen_bottle, counter = -1;
    float distance_to_closer_chosen_bottle;
    bool founded_earlier = false;
    for (bottle cur_bottle: SceneBuilder::all_bottles_coordinates) {
        counter++;
        glm::vec3 distance = cur_bottle.center - position;
//        float dot_product = dot(distance.x, ray_wor.x) + dot(distance.y, ray_wor.y) + dot(distance.z, ray_wor.z);
        float dot_product = dot(distance.x , ray_wor.x) + dot(distance.y, ray_wor.y) + dot(distance.z, ray_wor.z);
        if (dot_product < 0) {          // object is behind the camera
            continue;
        }
        else {      // object is in front of camera
            float angle = angleBetween(distance,ray_wor);
            float distance_length = sqrt((distance.x*distance.x) + (distance.y*distance.y) + (distance.z * distance.z));
            float distance_to_projection_of_center = sin(angle) * distance_length;
            if (distance_to_projection_of_center <= cur_bottle.width) {     // collision detected
                //cout << "\nCollision with bottle " << counter  <<"\n";
                if (!founded_earlier) {
                    distance_to_closer_chosen_bottle = distance_length;
                    chosen_bottle = counter;
                    founded_earlier = true;
                }
                if (distance_to_closer_chosen_bottle > distance_length) {
                    distance_to_closer_chosen_bottle = distance_length;
                    chosen_bottle = counter;
                }
            }
        }
    }
    if (!founded_earlier)   return NO_BOTTLE_COLLISION;
    else cout << "Collision with bottle " << chosen_bottle  <<"\n\n";
    return chosen_bottle;
}
