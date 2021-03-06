//
// Created by cosmos on 9/7/20.
//

#ifndef TEST_PARTICLE_BASE_HPP
#define TEST_PARTICLE_BASE_HPP
#include "libs.hpp"
#include "shader.hpp"
namespace particle{
    const float kParticleLauncher = 0.0f;
    const float kParticleShell = 1.0f;
    const glm::vec3 kMaxVelocity = glm::vec3(0.0,5.0,0.0);
    const glm::vec3 kMinVelocity = glm::vec3(0.0,3.0,0.0);
    const float kMaxLife = 2.0f * 1000;
    const float kMinLife = 1.0f * 1000;
    const float kParticleInitSize = 30.0f;
    const int kMaxParticle = 18000;
    const int kInitParticle = 10000;
    const glm::vec3 center(0.0f);
    const float r = 0.3f;

    struct baseParticle
    {
        float type;
        glm::vec3 position;
        glm::vec3 velocity;
        float lifetimeMills;
        float alpha;
        float size;
        float life;
    };
    template<typename particleType>
    class Particle{
    public:
        Particle() = default;
        virtual ~Particle() = default;
        void Render(float deltaTime, glm::mat4& projection,
                    glm::mat4 &view, glm::mat4& model)
        {
            mTimer += deltaTime * 1000.0f;
            updateParticles(deltaTime*1000.0f);
            renderParticles(projection, view, model);
            mCurRenderSet = !mCurRenderSet;
        }
    protected:
        void initParticles(int maxParticle, int initParticle){
            particles.resize(maxParticle);
            initParticleLocation(&particles[0], initParticle);
            glGenTransformFeedbacks(2, mTransformFeedbacks);
            glGenBuffers(2, mParticleBuffers);
            glGenVertexArrays(2, mParticleArrays);
            for (int i = 0; i < 2; i++)
            {
                glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, mTransformFeedbacks[i]);
                glBindBuffer(GL_ARRAY_BUFFER, mParticleBuffers[i]);
                glBindVertexArray(mParticleArrays[i]);
                glBufferData(GL_ARRAY_BUFFER, sizeof(particles[0]) * particles.size(), &particles[0], GL_DYNAMIC_DRAW);
                glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, mParticleBuffers[i]);
            }
            glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
            glBindVertexArray(0);
            mUpdateShader->use();
            glBindTexture(GL_TEXTURE_1D, mRandomTexture);
            mUpdateShader->setInt("gRandomTexture", 0);
        }
        virtual void initParticleLocation(particleType *particle, int initNums) = 0;
        virtual void updateParticles(float deltaTime) = 0;
        virtual void renderParticles(glm::mat4 &projection, glm::mat4 &view, glm::mat4 &model) = 0;
        bool mCurRenderSet;
        unsigned mParticleBuffers[2], mParticleArrays[2], mTransformFeedbacks[2];
        unsigned mRandomTexture, mSparkTexture, mStartTexture;
        float mTimer;
        bool mFirst;
        std::shared_ptr<shader::MyShader> mUpdateShader, mRenderShader;
        std::vector<particleType> particles;
    };
}

#endif //TEST_PARTICLE_BASE_HPP
