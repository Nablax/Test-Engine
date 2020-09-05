//
// Created by cosmos on 8/21/20.
//
#pragma once
#ifndef TEST_LIBS_HPP
#define TEST_LIBS_HPP

#define STB_IMAGE_IMPLEMENTATION
#include <../gl_libs/stb_image.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace const_value{
    const double gravity = 9.8;
    const glm::vec3 FRONT(0.0f, 0.0f, -1.0f);
    const glm::vec3 WORLDUP(0.0f, 1.0f, 0.0f);
}

#endif //TEST_LIBS_HPP
