//
// Created by cosmos on 8/21/20.
//

#ifndef TEST_BASE_HPP
#define TEST_BASE_HPP
#include "libs.hpp"
#include "shader.hpp"
class base{
public:
    base()=default;
    base(unsigned int vao, unsigned int vbo):mVAO(vao), mVBO(vbo){}
    explicit base(const std::shared_ptr<shader::MyShader> &inShader){linkShader(inShader);};
    virtual ~base() = default;
    virtual void render(shader::MyShader &s, glm::mat4 &view, glm::mat4 &projection, glm::mat4 &model){
        s.use();
        s.setMat4("view", view);
        s.setMat4("projection", projection);
        s.setMat4("model", model);
        glBindVertexArray(mVAO);
        if(mTexture){
            activate2DTexture(0, mTexture);
        }
        glDrawArrays(GL_TRIANGLES, 0, mNumTriangle);
        glBindVertexArray(0);
    }

    void linkShader(const std::shared_ptr<shader::MyShader> &inShader){
        mShader = inShader;
        std::cout<<"shader linked" << std::endl;
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

    void activate2DTexture(int textureOffset, unsigned textureID) const{
        glActiveTexture(GL_TEXTURE0 + textureOffset);
        glBindTexture(GL_TEXTURE_2D, textureID);
    }

protected:
    unsigned int mVAO, mVBO, mTexture=0, mNumTriangle;
    std::shared_ptr<shader::MyShader> mShader= nullptr;
};

#endif //TEST_BASE_HPP
