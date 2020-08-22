//
// Created by cosmos on 8/21/20.
//

#include "camera.h"

Camera::MyCamera::MyCamera(glm::vec3 position, glm::vec3 worldup, float yaw, float pitch)
    : Front(Camera::FRONT), CameraSpeed(Camera::SPEED), MouseSensitivity(Camera::SENSITIVITY), Zoom(Camera::ZOOM){
    Position = position;
    WorldUp = worldup;
    Yaw = yaw;
    Pitch = pitch;
    updateCamera();
}

glm::mat4 Camera::MyCamera::GetViewMatrix() {
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::MyCamera::ProcessKeyboardInput(Camera::Camera_Direction dir, float time) {
    float shift = CameraSpeed * time;
    switch (dir) {
        case FORWARD:
            Position += Front * shift;
            break;
        case BACKWARD:
            Position -= Front * shift;
            break;
        case LEFT:
            Position -= Right * shift;
            break;
        case RIGHT:
            Position += Right * shift;
            break;
    }
}

void Camera::MyCamera::ProcessMouseScroll(float offsetY) {
    Zoom -= offsetY;
    if (Zoom < ZOOMMIN)
        Zoom = ZOOMMIN;
    if (Zoom > ZOOMMAX)
        Zoom = ZOOMMAX;
}

void Camera::MyCamera::ProcessMouseMovement(float offsetX, float offsetY, GLboolean noFlip) {
    Yaw += offsetX * MouseSensitivity;
    Pitch += offsetY * MouseSensitivity;
    if (noFlip)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }
    updateCamera();
}

void Camera::MyCamera::updateCamera() {
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    newFront.y = sin(glm::radians(Pitch));
    newFront.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(newFront);
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}
