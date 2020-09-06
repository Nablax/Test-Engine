//
// Created by cosmos on 8/21/20.
//

#ifndef TEST_BASE_HPP
#define TEST_BASE_HPP
#include "libs.hpp"
#include "shader.hpp"
class base{
public:
public:
    base()=default;
    base(unsigned int vao, unsigned int vbo):mVAO(vao), mVBO(vbo){}
    virtual ~base() = default;
    virtual void render(shader::MyShader &s, glm::mat4 &view, glm::mat4 &projection, glm::mat4 &model){
        s.use();
        s.setMat4("view", view);
        s.setMat4("projection", projection);
        s.setMat4("model", model);
        glBindVertexArray(mVAO);
        glDrawArrays(GL_TRIANGLES, 0, mNumTriangle);
        glBindVertexArray(0);
    }

    void loadTexture(const std::string& path){
        if(mTexture){
            glDeleteTextures(1, &mTexture);
        }
        mTexture = textureutils::loadTexture(path);
    }

    void loadTexture(unsigned int textureID){
        if(mTexture){
            glDeleteTextures(1, &mTexture);
        }
        mTexture = textureID;
    }

protected:
    unsigned int mVAO, mVBO, mTexture, mNumTriangle;
};

#endif //TEST_BASE_HPP
