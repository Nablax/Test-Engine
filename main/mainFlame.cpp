//#define GLEW_STATIC
//#pragma comment(lib,"glew.lib")

#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <glm/glm.hpp>
#include <string>
#include "Flame.hpp"
#include <GLFW/glfw3.h>
#include "skybox.hpp"

void key_callback(GLFWwindow* window,int key, int scancode,int action,int mode);
void do_movement();
void mouse_callback(GLFWwindow* window,double xpos,double ypos);
void scroll_callback(GLFWwindow* window,double xoffset,double yoffset);

GLfloat screenWidth = 1600;
GLfloat screenHeight = 1000;
camera::MyCamera myCamera(glm::vec3(0.0f,8.0f,25.0f));
bool keys[1024];
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
GLfloat lastX = 400,lastY = 300;
bool firstMouse = true;
std::string str_fps;
char c[8];
int FrameRate = 0;
int FrameCount = 0;
int timeLeft = 0;


int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(screenWidth,screenHeight,"Learn OpenGL",NULL,NULL);
    if(window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window,mouse_callback);
    glfwSetScrollCallback(window,scroll_callback);
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK){
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }
    glViewport(0,0,screenWidth,screenHeight);
    Flame::Flame flame;
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    skybox::Skybox skybox;

    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
        do_movement();
        //render
        glClearColor(0.0,0.0,0.0,1.0);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection(1.0f);
        glm::mat4 model(1.0f);
        glm::mat4 view = myCamera.GetViewMatrix();
        projection = glm::perspective(glm::radians(45.0f),screenWidth/screenHeight,0.1f,2000.f);
        flame.Render(deltaTime, model, view, projection);
        skybox.render(view, projection);

        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();

    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window,GL_TRUE);
    if(action == GLFW_PRESS)
        keys[key] = true;
    else if(action == GLFW_RELEASE)
        keys[key] = false;
}

void do_movement(){
    GLfloat cameraSpeed = 5.0f*deltaTime;
    if(keys[GLFW_KEY_W])
        myCamera.ProcessKeyboardInput(camera::kForward,deltaTime);
    if(keys[GLFW_KEY_S])
        myCamera.ProcessKeyboardInput(camera::kBackward,deltaTime);
    if(keys[GLFW_KEY_A])
        myCamera.ProcessKeyboardInput(camera::kLeft,deltaTime);
    if(keys[GLFW_KEY_D])
        myCamera.ProcessKeyboardInput(camera::kRight,deltaTime);
}

void mouse_callback(GLFWwindow* window,double xpos,double ypos){
    if(firstMouse){
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
    myCamera.ProcessMouseMovement(xoffset,yoffset);
}

void scroll_callback(GLFWwindow* window,double xoffset,double yoffset){
    myCamera.ProcessMouseScroll(yoffset);
}