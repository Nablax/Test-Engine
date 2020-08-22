//
// Created by cosmos on 8/3/20.
//
#ifndef SKYBOX_HPP
#define SKYBOX_HPP

#include <utility>

#include "libs.hpp"
#include "shader.hpp"
#include "texture.hpp"

namespace skybox{
    const std::string vsPath = "../shader/skybox.vs";
    const std::string fsPath = "../shader/skybox.fs";
    const std::vector<std::string> faces
        {
            "../texture/skybox/right.jpg",
            "../texture/skybox/left.jpg",
            "../texture/skybox/top.jpg",
            "../texture/skybox/bottom.jpg",
            "../texture/skybox/front.jpg",
            "../texture/skybox/back.jpg"
        };
    float skyboxVertices[] = {
        // positions
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f
    };
    class Skybox{
    public:
        Skybox(std::vector<std::string> facePath = faces):skyboxShader(Shader(vsPath, fsPath)){
            skyboxTexture = TextureUtils::loadCubemap(std::move(facePath));
            skyboxShader.use();
            skyboxShader.setInt("skybox", 0);
            activateSkyboxTexture(0);
            glGenVertexArrays(1, &skyboxVAO);
            glGenBuffers(1, &skyboxVBO);
            glBindVertexArray(skyboxVAO);
            glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        }
        ~Skybox(){
            glDeleteVertexArrays(1, &skyboxVAO);
            glDeleteBuffers(1, &skyboxVBO);
        }
        void render(glm::mat4 view, glm::mat4 projection){
            glDepthFunc(GL_LEQUAL);
            skyboxShader.use();
            skyboxShader.setMat4("view", glm::mat4(glm::mat3(view)));
            skyboxShader.setMat4("projection", projection);
            glBindVertexArray(skyboxVAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glBindVertexArray(0);
            glDepthFunc(GL_LESS);
        }
        void activateSkyboxTexture(int textureOffset){
            glActiveTexture(GL_TEXTURE0 + textureOffset);
            glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
        }
    private:
        unsigned int skyboxVAO, skyboxVBO, skyboxTexture;
        Shader skyboxShader;
    };
}


#endif //RAY_TRACING_SKYBOX_HPP