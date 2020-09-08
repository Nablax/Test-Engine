//
// Created by cosmos on 8/21/20.
//
#pragma once
#ifndef TEST_LIBS_HPP
#define TEST_LIBS_HPP

#define STB_IMAGE_IMPLEMENTATION
#include <../gl_libs/stb_image.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

namespace constvalue{
    const double gravity = 9.8;
    const glm::vec3 kFront(0.0f, 0.0f, -1.0f);
    const glm::vec3 kWorldUp(0.0f, 1.0f, 0.0f);
    const unsigned int kScreenWidth = 800;
    const unsigned int kScreenHeight = 600;
}

#endif //TEST_LIBS_HPP
