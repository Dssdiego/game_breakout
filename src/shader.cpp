//
// Created by Diego Santos Seabra on 26/03/21.
//

#define GL_GLEXT_PROTOTYPES
#define GL_SILENCE_DEPRECATION

#ifdef _WIN32
#include <glew.h>
#else
#include <SDL_opengl.h>
#include <SDL_opengl_glext.h>
#endif
#include "shader.h"

Shader &Shader::Use()
{
    glUseProgram(this->Id);
    return *this;
}

//void Shader::SetFloat(const char *name, float value, bool useShader)
//{
//    if (useShader)
//    {
//        this->Use();
//    }
//    glUniform1i(glGetUniformLocation(this->Id, name), value);
//}

