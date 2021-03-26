//
// Created by Diego Santos Seabra on 26/03/21.
//

#define GL_GLEXT_PROTOTYPES
#define GL_SILENCE_DEPRECATION

#include <glew.h>
#include "shader.h"

Shader &Shader::Use()
{
    glUseProgram(this->Id);
    return *this;
}

void Shader::SetFloat(const char *name, float value, bool useShader)
{
    if (useShader)
    {
        this->Use();
    }
    glUniform1i(glGetUniformLocation(this->Id, name), value);
}

