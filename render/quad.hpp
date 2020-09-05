//
// Created by cosmos on 8/21/20.
//

#ifndef TEST_QUAD_HPP
#define TEST_QUAD_HPP

#include "texture.hpp"
#include "shader.hpp"
#include <base.hpp>

namespace quad{
    float planeVertices[] = {
            // positions            // normals         // texcoords
            10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
            -10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
            -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,

            10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
            -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
            10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,  10.0f, 10.0f
    };

    const std::string defaultVsPath = "../shader/plane.vs";
    const std::string defaultFsPath = "../shader/plane.fs";
    const std::string defaultTexture = "../texture/wood.png";

    unsigned int VAO = 0, VBO = 0;

    void genQuad(){
        if(VAO != 0)
            return;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glBindVertexArray(0);
    }

    class MyQuad: public base{
    public:
        MyQuad(){
            genQuad();
            mVAO = VAO;
            mVBO = VBO;
            textureID = textureutils::loadTexture(defaultTexture);
        }
        MyQuad(unsigned int vao, unsigned int vbo, unsigned int textureid = 0): base(vao, vbo), textureID(textureid){

        }
    private:
        unsigned int textureID;
    };
};

#endif //TEST_QUAD_HPP
