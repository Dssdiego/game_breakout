//
// Created by Diego Santos Seabra on 26/03/21.
//

#ifndef BREAKOUT_SHADER_H
#define BREAKOUT_SHADER_H

#include <string>
#include <glm/glm.hpp>

class Shader
{
public:
    unsigned int Id;

    Shader();

    // Sets the current shader as active
    Shader &Use();

    // Compiles the shader from a given source code
    void Compile(const char *source);

    // Utility functions
    void SetFloat(const char *name, float value, bool useShader = false);
    void SetInteger(const char *name, int value, bool useShader = false);
    void SetVector2f(const char *name, float x, float y, bool useShader = false);
    void SetVector2f(const char *name, glm::vec2 &value, bool useShader = false);
    void SetVector3f(const char *name, float x, float y, float z, bool useShader = false);
    void SetVector3f(const char *name, glm::vec3 &value, bool useShader = false);
    void SetVector4f(const char *name, float x, float y, float z, float w, bool useShader = false);
    void SetVector4f(const char *name, glm::vec4 &value, bool useShader = false);
    void SetMatrix4(const char *name, glm::mat4 &matrix, bool useShader = false);
private:
    // Checks if compilation or linking failed and if so, print the error logs
    void checkCompileErrors(unsigned int object, std::string type);
};

#endif //BREAKOUT_SHADER_H
