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
    unsigned int id;

    Shader();

    // Sets the current shader as active
    Shader &use();

    // Compiles the shader from a given source code
    void compile(const char *source);

    // Utility functions
    void setFloat(const char *name, float value, bool useShader = false);
    void setInteger(const char *name, int value, bool useShader = false);
    void setVector2f(const char *name, float x, float y, bool useShader = false);
    void setVector2f(const char *name, glm::vec2 &value, bool useShader = false);

private:
    // Checks if compilation or linking failed and if so, print the error logs
    void checkCompileErrors(unsigned int object, std::string type);
};

#endif //BREAKOUT_SHADER_H
