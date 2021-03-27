//
// Created by Diego Santos Seabra on 27/03/21.
//

#ifndef BREAKOUT_RESOURCE_MANAGER_H
#define BREAKOUT_RESOURCE_MANAGER_H

#include <string>
#include <map>
#include <vector>
#include "shader.h"
#include "texture.h"

class ResourceManager
{
public:
    static std::map<std::string, Shader> Shaders;
    static std::map<std::string, Texture2D> Textures;

    // Shaders
    static Shader LoadShader(const char *shaderFile, std::string name);
    static Shader GetShader(std::string name);

    // Textures
    static Texture2D LoadTexture(const char *file, bool alpha, std::string name);
    static Texture2D GetTexture(std::string name);

    // Cleanup
    static void Clear(); // de-allocates all loaded resources
private:
    ResourceManager() {}

    // Loads and generate a shader from file
    static Shader loadShaderFromFile(const char *shaderFile);

    // Loads a single texture from file
    static Texture2D loadTextureFromFile(const char *file, bool alpha);
};


#endif //BREAKOUT_RESOURCE_MANAGER_H
