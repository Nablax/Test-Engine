//
// Created by cosmos on 8/3/20.
//
#ifndef SKYBOX_HPP
#define SKYBOX_HPP

#include <utility>

#include "libs.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "base.hpp"

namespace skybox{
    const std::string vsPath = "../shader/skybox.vs";
    const std::string fsPath = "../shader/skybox.fs";
    const std::vector<std::string> faces{
            "../texture/skybox/right.jpg",
            "../texture/skybox/left.jpg",
            "../texture/skybox/top.jpg",
            "../texture/skybox/bottom.jpg",
            "../texture/skybox/front.jpg",
            "../texture/skybox/back.jpg"
        };
    const float skyboxVertices[] = {
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
class Skybox: public base{
    public:
        explicit Skybox(std::vector<std::string> facePath = faces, const std::string& vsp = skybox::vsPath,
               const std::string& fsp = skybox::fsPath):skyboxShader(shader::MyShader(vsp, fsp)){
            skyboxTexture = textureutils::loadCubemap(std::move(facePath));
            skyboxShader.use();
            skyboxShader.setInt("skybox", 0);
            activateSkyboxTexture(0);
            glGenVertexArrays(1, &mVAO);
            glGenBuffers(1, &mVBO);
            glBindVertexArray(mVAO);
            glBindBuffer(GL_ARRAY_BUFFER, mVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        }
        virtual ~Skybox() = default;
        void render(glm::mat4 view, glm::mat4 projection){
            glDepthFunc(GL_LEQUAL);
            skyboxShader.use();
            skyboxShader.setMat4("view", glm::mat4(glm::mat3(view)));
            skyboxShader.setMat4("projection", projection);
            glBindVertexArray(mVAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glBindVertexArray(0);
            glDepthFunc(GL_LESS);
        }
        void activateSkyboxTexture(int textureOffset) const{
            glActiveTexture(GL_TEXTURE0 + textureOffset);
            glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
        }
    private:
        unsigned int skyboxTexture;
        shader::MyShader skyboxShader;
    };
}


#endif //RAY_TRACING_SKYBOX_HPP