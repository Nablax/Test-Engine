cmake_minimum_required(VERSION 3.16)
project(test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE DEBUG)
include_directories(gl_libs my_classes render)
add_executable(test main.cpp gl_libs/glad.c my_classes/shader.h gl_libs/stb_image.h my_classes/camera.h my_classes/mesh.h my_classes/model.h render/skybox.h utils/camera.cpp utils/camera.h)
target_link_libraries(test glfw3 pthread GL Xrandr Xi X11 Xxf86vm dl Xinerama Xcursor assimp)

