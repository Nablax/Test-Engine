//
// Created by cosmos on 8/21/20.
//
#ifndef TEST_CAMERA_HPP
#define TEST_CAMERA_HPP

#include "libs.hpp"

namespace Camera{

    const glm::vec3 FRONT(0.0f, 0.0f, -1.0f);

    const glm::vec3 POSITION = glm::vec3(0.0f);

    const float YAW = -90.0f;
    const float PITCH = 0.0f;
    const float SPEED = 2.5f;
    const float SENSITIVITY = 0.1f;
    const float ZOOM = 45.0f;
    const float ZOOMMIN = 1.0f;
    const float ZOOMMAX = 45.0f;

    enum Camera_Direction {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    class MyCamera {
    public:
        MyCamera(glm::vec3 position, glm::vec3 worldup = const_value::WORLDUP, float yaw=YAW, float pitch=PITCH)
                : Front(Camera::FRONT), CameraSpeed(Camera::SPEED), MouseSensitivity(Camera::SENSITIVITY), Zoom(Camera::ZOOM){
            Position = position;
            WorldUp = worldup;
            Yaw = yaw;
            Pitch = pitch;
            updateCamera();
        }
        glm::mat4 GetViewMatrix() {
            return glm::lookAt(Position, Position + Front, Up);
        }
        void ProcessKeyboardInput(Camera::Camera_Direction dir, float time) {
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
        void ProcessMouseMovement(float offsetX, float offsetY, GLboolean noFlip=true) {
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
        void ProcessMouseScroll(float offsetY) {
            Zoom -= offsetY;
            if (Zoom < ZOOMMIN)
                Zoom = ZOOMMIN;
            if (Zoom > ZOOMMAX)
                Zoom = ZOOMMAX;
        }

    private:
        glm::vec3 Position, Front, Up, Right;
        glm::vec3 WorldUp;
        float Yaw, Pitch;
        float CameraSpeed, MouseSensitivity, Zoom;
        void updateCamera() {
            glm::vec3 newFront;
            newFront.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
            newFront.y = sin(glm::radians(Pitch));
            newFront.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
            Front = glm::normalize(newFront);
            Right = glm::normalize(glm::cross(Front, WorldUp));
            Up = glm::normalize(glm::cross(Right, Front));
        }
    };
}

#endif //TEST_CAMERA_HPP
