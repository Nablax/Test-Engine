cmake_minimum_required(VERSION 3.16)
project(test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE DEBUG)
include_directories(gl_libs render utils particles)
add_executable(test main.cpp gl_libs/glad.c gl_libs/stb_image.h render/skybox.hpp utils/camera.hpp utils/libs.hpp utils/texture.hpp render/cube.hpp render/quad.hpp render/base.hpp render/sphere.hpp render/physics.hpp)
#add_executable(test main/mainFlame.cpp utils/camera.hpp utils/libs.hpp utils/texture.hpp particles/Flame.hpp particles/particle_base.hpp)
target_link_libraries(test glfw3 pthread GL GLEW Xrandr Xi X11 Xxf86vm dl Xinerama Xcursor assimp)

