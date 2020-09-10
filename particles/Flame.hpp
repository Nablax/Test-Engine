#pragma once
#ifndef TEST_FLAME_HPP
#define TEST_FLAME_HPP
#include "camera.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "particle_base.hpp"
namespace Flame {

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

    struct FlameParticle: particle::baseParticle
    {

    };

    class Flame: public particle::Particle<FlameParticle>
    {
    public:
        Flame()
        {
            glGetError();
            mCurRenderSet = 0;
            mFirst = true;
            mTimer = 0;
            const GLchar* varyings[7] = { "Type1","Position1",
                                          "Velocity1","Age1",
                                          "Alpha1","Size1",
                                          "Life1"
            };//设置TransformFeedback要捕获的输出变量
            mUpdateShader = std::make_shared<shader::MyShader>("../test_shader/Update.vs", "../test_shader/Update.fs",
                                                 "../test_shader/Update.gs", varyings, 7);
            //设置TransformFeedback缓存能够记录的顶点的数据类型

            mRenderShader = std::make_shared<shader::MyShader>("../test_shader/Render.vs", "../test_shader/Render.fs");
            //设置随机纹理
            InitRandomTexture(580);
            mSparkTexture = textureutils::loadTexture("../texture/particle.bmp");
            mStartTexture = textureutils::loadTexture("../texture/flame.bmp");
            mRenderShader->use();
            mRenderShader->setInt("flameSpark", 0);
            mRenderShader->setInt("flameStart", 1);
            initParticles();
        }
        ~Flame()=default;
        void Render(float frametimeMills, glm::mat4& worldMatrix,
                    glm::mat4 viewMatrix, glm::mat4& projectMatrix)
        {
            mTimer += frametimeMills*1000.0f;
            UpdateParticles(frametimeMills*1000.0f);
            RenderParticles(worldMatrix, viewMatrix, projectMatrix);
            mCurRenderSet = !mCurRenderSet;
        }
    private:
        void UpdateParticles(float frametimeMills)
        {
            mUpdateShader->use();
            mUpdateShader->setFloat("gDeltaTimeMillis", frametimeMills);
            mUpdateShader->setFloat("gTime", mTimer);
            mUpdateShader->setFloat("MAX_LIFE", kMaxLife);
            mUpdateShader->setFloat("MIN_LIFE", kMinLife);
            mUpdateShader->setVec3("MAX_VELOC", kMaxVelocity);
            mUpdateShader->setVec3("MIN_VELOC", kMinVelocity);

            //绑定纹理
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_1D, mRandomTexture);
            //mUpdateShader->setInt("gRandomTexture",0);

            glEnable(GL_RASTERIZER_DISCARD);//我们渲染到TransformFeedback缓存中去，并不需要光栅化
            glBindVertexArray(mParticleArrays[mCurRenderSet]);
            glBindBuffer(GL_ARRAY_BUFFER, mParticleBuffers[mCurRenderSet]);
            glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, mTransformFeedbacks[!mCurRenderSet]);

            glEnableVertexAttribArray(0);//type
            glEnableVertexAttribArray(1);//position
            glEnableVertexAttribArray(2);//velocity
            glEnableVertexAttribArray(3);//lifetime
            glEnableVertexAttribArray(4);//alpha
            glEnableVertexAttribArray(5);//size
            glEnableVertexAttribArray(6);//life
            glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, sizeof(FlameParticle), (void*)offsetof(FlameParticle, type));
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(FlameParticle), (void*)offsetof(FlameParticle, position));
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(FlameParticle), (void*)offsetof(FlameParticle, velocity));
            glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(FlameParticle), (void*)offsetof(FlameParticle, lifetimeMills));
            glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(FlameParticle), (void*)offsetof(FlameParticle, alpha));
            glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, sizeof(FlameParticle), (void*)offsetof(FlameParticle, size));
            glVertexAttribPointer(6, 1, GL_FLOAT, GL_FALSE, sizeof(FlameParticle), (void*)offsetof(FlameParticle, life));
            glBeginTransformFeedback(GL_POINTS);
            if (mFirst)
            {
                glDrawArrays(GL_POINTS, 0, kInitParticle);
                mFirst = false;
            }
            else {
                glDrawTransformFeedback(GL_POINTS, mTransformFeedbacks[mCurRenderSet]);
            }
            glEndTransformFeedback();
            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
            glDisableVertexAttribArray(2);
            glDisableVertexAttribArray(3);
            glDisableVertexAttribArray(4);
            glDisableVertexAttribArray(5);
            glDisableVertexAttribArray(6);
            glDisable(GL_RASTERIZER_DISCARD);
            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
        void InitRandomTexture(unsigned int size)
        {
            srand(time(NULL));
            auto* pRandomData = new glm::vec3[size];

            for (int i = 0; i < size; i++)
            {
                pRandomData[i].x = float(rand()) / float(RAND_MAX);
                pRandomData[i].y = float(rand()) / float(RAND_MAX);
                pRandomData[i].z = float(rand()) / float(RAND_MAX);
            }
            glGenTextures(1, &mRandomTexture);
            glBindTexture(GL_TEXTURE_1D, mRandomTexture);
            glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, size, 0, GL_RGB, GL_FLOAT, pRandomData);
            glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            delete[] pRandomData;
            pRandomData = nullptr;
        }
        void RenderParticles(glm::mat4& worldMatrix,
                             glm::mat4& viewMatrix, glm::mat4& projectMatrix)
        {
            glEnable(GL_PROGRAM_POINT_SIZE);
            glDisable(GL_DEPTH_TEST);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);

            mRenderShader->use();
            mRenderShader->setMat4("model", worldMatrix);
            mRenderShader->setMat4("view", viewMatrix);
            mRenderShader->setMat4("projection", projectMatrix);
            glBindVertexArray(mParticleArrays[!mCurRenderSet]);
            glBindBuffer(GL_ARRAY_BUFFER, mParticleBuffers[!mCurRenderSet]);
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glEnableVertexAttribArray(2);
            glEnableVertexAttribArray(3);
            glEnableVertexAttribArray(4);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(FlameParticle), (void*)offsetof(FlameParticle, position));
            glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(FlameParticle), (void*)offsetof(FlameParticle, alpha));
            glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(FlameParticle), (void*)offsetof(FlameParticle, size));
            glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(FlameParticle), (void*)offsetof(FlameParticle, lifetimeMills));
            glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(FlameParticle), (void*)offsetof(FlameParticle, life));

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, mSparkTexture);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, mStartTexture);
            glDrawTransformFeedback(GL_POINTS, mTransformFeedbacks[!mCurRenderSet]);
            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
            glDisableVertexAttribArray(2);
            glDisableVertexAttribArray(3);
            glDisableVertexAttribArray(4);
            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glEnable(GL_DEPTH_TEST);
        }
        void initParticleLocation(FlameParticle *particles, int nums) override
        {
            srand(time(NULL));
            int n = 10;
            float Adj_value = 0.05f;
            float radius = 0.7f;//火焰地区半径
            auto deltaVelocity = kMaxVelocity - kMinVelocity;
            for (int x = 0; x < nums; x++) {
                glm::vec3 record(0.0f);
                for (int y = 0; y < n; y++) {//生成高斯分布的粒子，中心多，外边少
                    record.x += (2.0f*float(rand()) / float(RAND_MAX) - 1.0f);
                    record.z += (2.0f*float(rand()) / float(RAND_MAX) - 1.0f);
                }
                record.x *= radius;
                record.z *= radius;
                record.y = center.y;
                particles[x].type = kParticleLauncher;
                particles[x].position = record;
                particles[x].velocity = deltaVelocity*(float(rand()) / float(RAND_MAX)) + kMinVelocity;//在最大最小速度之间随机选择
                particles[x].alpha = 1.0f;
                particles[x].size = kParticleInitSize;//发射器粒子大小
                //在最短最长寿命之间随机选择
                particles[x].lifetimeMills = (kMaxLife - kMinLife)*(float(rand()) / float(RAND_MAX)) + kMinLife;
                float dist = sqrt(record.x*record.x + record.z*record.z);
                particles[x].life = particles[x].lifetimeMills;
            }
        }
    };

}

#endif