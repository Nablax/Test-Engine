//
// Created by cosmos on 9/7/20.
//

#ifndef TEST_PARTICLE_BASE_HPP
#define TEST_PARTICLE_BASE_HPP
#include "libs.hpp"
#include "shader.hpp"
namespace particle{
    struct ParticleAttribute
    {
        float type;
        glm::vec3 position;
        glm::vec3 velocity;
        float lifetimeMills;
        float alpha;
        float size;
        float life;
    };
    class Particle{
    private:
        unsigned int mCurVBOIndex, mCurTransformFeedbackIndex;
        GLuint mParticleBuffers[2]; //粒子发射系统的两个顶点缓存区
        GLuint mParticleArrays[2];
        GLuint mTransformFeedbacks[2];//粒子发射系统对应的TransformFeedback
        GLuint mRandomTexture;//随机一维纹理
        unsigned mSparkTexture;//Alpha纹理
        unsigned mStartTexture;
        float mTimer;//粒子发射器已经发射的时间
        bool mFirst;
        shader::MyShader* mUpdateShader;//更新粒子的GPUProgram
        shader::MyShader* mRenderShader;//渲染粒子的GPUProgram
    };
}

#endif //TEST_PARTICLE_BASE_HPP
