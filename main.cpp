#include <memory>

#include "camera.hpp"
#include "skybox.hpp"
#include "cube.hpp"
#include "quad.hpp"
#include "sphere.hpp"
#include "libs.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);
void processInput(GLFWwindow *window);

// camera
camera::MyCamera myCamera(glm::vec3(0.0f, 0.0f, 3.0f));
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

double lastMouseX, lastMouseY;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(constvalue::kScreenWidth, constvalue::kScreenHeight, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if(glewInit() != GLEW_OK){
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    skybox::Skybox skybox;
    sphere::MySphere sphere(std::make_shared<shader::MyShader>(sphere::kDefaultVsPath, sphere::kDefaultFsPath));
    quad::MyQuad ground(std::make_shared<shader::MyShader>(quad::kDefaultVsPath, quad::kDefaultFsPath));

    float a = 9.8;
    float v = 0;
    float path = -5;
    float floor = 10;

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);
        glClearColor(0.5f, 0.7f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = myCamera.GetViewMatrix();
        glm::mat4 projection =
                glm::perspective(glm::radians(camera::kZoom), static_cast<float>(constvalue::kScreenWidth)
                / static_cast<float>(constvalue::kScreenHeight), 0.1f, 100.0f);


        skybox.render(projection, view);

        glm::mat4 model = glm::mat4(1.0f);
        v += a * deltaTime;
        path += v * deltaTime / 2;
        if(path > floor + 1)
            v *= -1;
        model = glm::translate(model, glm::vec3(-1.0f, 0.0f - path, -1.0f));
        model = glm::scale(model, glm::vec3(0.1));
        sphere.render(projection, view, model);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f - floor, -1.0f));
        ground.render(projection, view, model);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        myCamera.ProcessKeyboardInput(camera::kForward, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        myCamera.ProcessKeyboardInput(camera::kBackward, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        myCamera.ProcessKeyboardInput(camera::kLeft, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        myCamera.ProcessKeyboardInput(camera::kRight, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
    if (firstMouse)
    {
        lastMouseX = xPos;
        lastMouseY = yPos;
        firstMouse = false;
    }
    myCamera.ProcessMouseMovement(xPos - lastMouseX, lastMouseY - yPos);
    lastMouseX = xPos;
    lastMouseY = yPos;
}


void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
{
    myCamera.ProcessMouseScroll(yOffset);
}
