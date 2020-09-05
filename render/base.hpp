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
    base(){
        VAO = 0;
        VBO = 0;
    }
    base(unsigned int vao, unsigned int vbo):VAO(vao), VBO(vbo){

    }
    ~base(){

    }
    virtual void render(shader::MyShader &s, glm::mat4 view, glm::mat4 projection, glm::mat4 model){
        s.use();
        s.setMat4("view", view);
        s.setMat4("projection", projection);
        s.setMat4("model", model);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
    }

protected:
    unsigned int VAO, VBO;
};

#endif //TEST_BASE_HPP
