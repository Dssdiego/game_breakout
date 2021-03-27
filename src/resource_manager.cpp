//
// Created by Diego Santos Seabra on 27/03/21.
//

#define GL_GLEXT_PROTOTYPES
#define GL_SILENCE_DEPRECATION
#define STB_IMAGE_IMPLEMENTATION

#ifdef _WIN32
#include <glew.h>
#else

#include <SDL_opengl.h>

#endif

#include "resource_manager.h"
#include <stb_image.h>
#include <iostream>
#include <fstream>

// Instantiate static variables
std::map<std::string, Texture2D> ResourceManager::Textures;
std::map<std::string, Shader> ResourceManager::Shaders;

Shader ResourceManager::LoadShader(const char *shaderFile, std::string name)
{
    Shaders[name] = loadShaderFromFile(shaderFile);
    return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name)
{
    return Shaders[name];
}

Texture2D ResourceManager::LoadTexture(const char *file, bool alpha, std::string name)
{
    Textures[name] = loadTextureFromFile(file, alpha);
    return Textures[name];
}

Texture2D ResourceManager::GetTexture(std::string name)
{
    return Textures[name];
}

void ResourceManager::Clear()
{
    // Delete all shaders
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.Id);

    // Delete all textures
    for (auto iter : Textures)
        glDeleteTextures(1, &iter.second.Id);
}

Shader ResourceManager::loadShaderFromFile(const char *shaderFile)
{
    // vertex | fragment | geometry
    std::vector<bool> shaderTypes = {false, false, false};

    std::ifstream fileStream(shaderFile, std::ios::in);
    std::string vertexStr, fragmentStr, geometryStr;
    std::vector<std::string> shaderStr;

    if (!fileStream.is_open())
        std::cerr << "Could not read file " << shaderFile << ". File does not exist." << std::endl;

    std::string line;
    while (!fileStream.eof())
    {
        std::getline(fileStream, line);

        if (line == "// vertex")
        {
            shaderTypes = {
                    true,   // vertex
                    false,  // fragment
                    false   // geometry
            };
        }

        if (line == "// fragment")
        {
            shaderTypes = {
                    false,  // vertex
                    true,   // fragment
                    false   // geometry
            };
        }

        if (line == "// geometry")
        {
            shaderTypes = {
                    false,  // vertex
                    false,  // fragment
                    true    // geometry
            };
        }

        if (shaderTypes[0] && line != "// vertex")
            vertexStr.append(line + "\n");

        if (shaderTypes[1] && line != "// fragment")
            fragmentStr.append(line + "\n");

        if (shaderTypes[2] && line != "// geometry")
            geometryStr.append(line + "\n");
    }

    shaderStr.push_back(vertexStr);
    shaderStr.push_back(fragmentStr);
    shaderStr.push_back(geometryStr);

    fileStream.close();

    // Create shader object from source code
    Shader shader;
    shader.Compile(shaderStr);
    return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const char *file, bool alpha)
{
    // Create texture object
    Texture2D texture2D;
    if (alpha)
    {
        texture2D.InternalFormat = GL_RGBA;
        texture2D.ImageFormat = GL_RGBA;
    }

    // Load image
    int width, height, nrChannels;
    unsigned char *data = stbi_load(file, &width, &height, &nrChannels, 0);

    // Generate texture
    texture2D.Generate(width, height, data);

    // Cleanup
    stbi_image_free(data);
    return texture2D;
}


