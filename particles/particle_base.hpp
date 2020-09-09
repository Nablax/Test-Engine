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
    protected:
        unsigned int mCurVBOIndex, mCurTransformFeedbackIndex;
        GLuint mParticleBuffers[2];
        GLuint mParticleArrays[2];
        GLuint mTransformFeedbacks[2];
        GLuint mRandomTexture;
        unsigned mSparkTexture;
        unsigned mStartTexture;
        float mTimer;
        bool mFirst;
        shader::MyShader* mUpdateShader;
        shader::MyShader* mRenderShader;
    };
}

#endif //TEST_PARTICLE_BASE_HPP
