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
    public:
        Particle(){
//            glGenTransformFeedbacks(2, mTransformFeedbacks);
//            glGenBuffers(2, mParticleBuffers);
//            glGenVertexArrays(2, mParticleArrays);
//            for (int i = 0; i < 2; i++)
//            {
//                glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, mTransformFeedbacks[i]);
//                glBindBuffer(GL_ARRAY_BUFFER, mParticleBuffers[i]);
//                glBindVertexArray(mParticleArrays[i]);
//                glBufferData(GL_ARRAY_BUFFER, sizeof(particles), particles, GL_DYNAMIC_DRAW);
//                glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, mParticleBuffers[i]);
//            }
//            glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
//            glBindVertexArray(0);
        }
    protected:
        bool mCurRenderSet;
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
