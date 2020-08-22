//
// Created by cosmos on 8/21/20.
//

#ifndef TEST_CAMERA_H
#define TEST_CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

namespace Camera{

    const glm::vec3 FRONT(0.0f, 0.0f, -1.0f);
    const glm::vec3 WORLDUP(0.0f, 1.0f, 0.0f);
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
        MyCamera(glm::vec3 position=Camera::POSITION, glm::vec3 worldup=Camera::WORLDUP, float yaw=Camera::YAW, float pitch=Camera::PITCH);
        glm::mat4 GetViewMatrix();
        void ProcessKeyboardInput(Camera_Direction dir, float time);
        void ProcessMouseMovement(float offsetX, float offsetY, GLboolean constrainPitch = true);
        void ProcessMouseScroll(float offsetY);

    private:
        void updateCamera();
        glm::vec3 Position, Front, Up, Right;
        glm::vec3 WorldUp;
        float Yaw, Pitch;
        float CameraSpeed, MouseSensitivity, Zoom;
    };
}

#endif //TEST_CAMERA_H
