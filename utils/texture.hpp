//
// Created by cosmos on 8/21/20.
//

#ifndef TEST_TEXTURE_HPP
#define TEST_TEXTURE_HPP

#include "libs.hpp"

namespace textureutils{
    const std::unordered_map<int, GLenum> channelToFormat {{1, GL_RED}, {3, GL_RGB} ,{4, GL_RGBA}};

    unsigned int loadTexture(const std::string& path)
    {
        unsigned int textureID;
        glGenTextures(1, &textureID);

        int width, height, numChannel;
        unsigned char *data = stbi_load(path.c_str(), &width, &height, &numChannel, 0);
        if(!data){
            std::cout << "Texture loading failed at: " << path << std::endl;
            stbi_image_free(data);
            return 0;
        }

        GLenum imageFormat = channelToFormat.at(numChannel);

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, imageFormat, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_image_free(data);
        return textureID;
    }

    unsigned int loadCubemap(std::vector<std::string> faces)
    {
        unsigned int textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

        int width, height, numChannel;
        for (unsigned int i = 0; i < faces.size(); i++)
        {
            unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &numChannel, 0);
            if(!data){
                std::cout << "Cubemap texture loading failed at: " << faces[i] << std::endl;
                stbi_image_free(data);
                return 0;
            }
            GLenum imageFormat = channelToFormat.at(numChannel);
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, imageFormat, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);

        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        return textureID;
    }
}

#endif //TEST_TEXTURE_HPP
