#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

// Lab 1: You can add more helper functions if you want!

glm::mat3 rotation(const float degrees,const glm::vec3 axis){
    const float radians = glm::radians(degrees); // convert to radians
    const float cosTheta = cos(radians);
    const float sinTheta = sin(radians);

    glm::mat3 I(1.0f); // Identity matrix
    glm::mat3 axisCrossProduct = glm::mat3(
        0, -axis.z, axis.y,
        axis.z, 0, -axis.x,
        -axis.y, axis.x, 0
    );
    glm::mat3 axisOuterProduct = glm::outerProduct(axis, axis);

    return cosTheta * I + sinTheta * axisCrossProduct + (1.0f - cosTheta) * axisOuterProduct;
}
// Rotate the camera around the target to the right
void Camera::rotateRight(const float degrees) {
    glm::mat3 rotMatrix = rotation(-degrees, up);
    glm::vec3 direction = eye - target; // direction from target to eye
    direction = rotMatrix * direction; // rotate the direction
    eye = target + direction; // update eye position
}

// Rotate the camera around the target upwards
void Camera::rotateUp(const float degrees) {
	glm::vec3 right = glm::normalize(glm::cross(target - eye, up)); // right vector from cross product
    glm::mat3 rotMatrix = rotation(degrees, right);
    glm::vec3 direction = eye - target; // direction from target to eye
    direction = rotMatrix * direction; // rotate the direction
    eye = target + direction; // update eye position
    up = rotMatrix * up; // update the up vector
}
void Camera::computeMatrices(){
    // Update the view matrix using eye, target, and up
    view = glm::lookAt(eye, target, up);

    // Update the projection matrix using aspect, fovy, nearDist, and farDist
    proj = glm::perspective(glm::radians(fovy), aspect, nearDist, farDist);
    
}

void Camera::reset(){
    eye = eye_default;// position of the eye
    target = target_default;  // look at target
    up = up_default;      // up vector
    fovy = fovy_default;  // field of view in degrees
    aspect = aspect_default; // aspect ratio
    nearDist = near_default; // nearDist clipping distance
    farDist = far_default; // farDist clipping distance
}