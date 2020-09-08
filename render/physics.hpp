//
// Created by cosmos on 9/6/20.
//

#ifndef TEST_PHYSICS_HPP
#define TEST_PHYSICS_HPP
#include "libs.hpp"
#include "base.hpp"
class physics{
public:
    physics(glm::vec3 a=glm::vec3(0, 9.8, 0), glm::vec3 v=glm::vec3(0),glm::vec3 pos=glm::vec3(0))
    :mAcceleration(a), mSpeed(v), mPosition(pos){}

    glm::vec3 update(float deltaTime){
        mPosition += (mSpeed + 0.5f * mAcceleration * deltaTime) * deltaTime;
        mSpeed += mAcceleration * deltaTime;

    }
    glm::vec3 getPosition(float deltaTime){
        return (mSpeed + 0.5f * mAcceleration * deltaTime) * deltaTime;
    }

    glm::vec4 getModelMatrix(){

    }
private:
    glm::vec3 mAcceleration, mSpeed, mPosition;
    float mScale;
};

#endif //TEST_PHYSICS_HPP
