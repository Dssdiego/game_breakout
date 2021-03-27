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

#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "shader.h"

Shader &Shader::Use()
{
    glUseProgram(this->Id);
    return *this;
}

void Shader::SetFloat(const char *name, float value, bool useShader)
{
    if (useShader)
        this->Use();
    glUniform1f(glGetUniformLocation(this->Id, name), value);
}

Shader &Shader::SetInteger(const char *name, int value, bool useShader)
{
    if (useShader)
        this->Use();
    glUniform1i(glGetUniformLocation(this->Id, name), value);
    return *this;
}

void Shader::SetVector2f(const char *name, float x, float y, bool useShader)
{
    if (useShader)
        this->Use();
    glUniform2f(glGetUniformLocation(this->Id, name), x, y);
}

void Shader::SetVector2f(const char *name, glm::vec2 &value, bool useShader)
{
    if (useShader)
        this->Use();
    glUniform2f(glGetUniformLocation(this->Id, name), value.x, value.y);
}

void Shader::SetVector3f(const char *name, float x, float y, float z, bool useShader)
{
    if (useShader)
        this->Use();
    glUniform3f(glGetUniformLocation(this->Id, name), x, y, z);
}

void Shader::SetVector3f(const char *name, glm::vec3 &value, bool useShader)
{
    if (useShader)
        this->Use();
    glUniform3f(glGetUniformLocation(this->Id, name), value.x, value.y, value.z);
}

void Shader::SetVector4f(const char *name, float x, float y, float z, float w, bool useShader)
{
    if (useShader)
        this->Use();
    glUniform4f(glGetUniformLocation(this->Id, name), x, y, z, w);
}

void Shader::SetVector4f(const char *name, glm::vec4 &value, bool useShader)
{
    if (useShader)
        this->Use();
    glUniform4f(glGetUniformLocation(this->Id, name), value.x, value.y, value.z, value.w);
}

void Shader::SetMatrix4(const char *name, glm::mat4 &matrix, bool useShader)
{
    if (useShader)
        this->Use();
    glUniformMatrix4fv(glGetUniformLocation(this->Id, name), 1, false, glm::value_ptr(matrix));
}

void Shader::Compile(std::vector<std::string> &source)
{
    GLuint vertShader, fragShader, geomShader;

    const char *vertShaderSrc = source[0].c_str();
    const char *fragShaderSrc = source[1].c_str();
    const char *geomShaderSrc = source[2].c_str();

    // Vertex shader
    vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, &vertShaderSrc, nullptr);
    glCompileShader(vertShader);

    checkCompileErrors(vertShader, ShaderObjectType::Vertex);

    // Fragment shader
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragShaderSrc, nullptr);
    glCompileShader(fragShader);

    checkCompileErrors(fragShader, ShaderObjectType::Fragment);

    // Geometry shader
    if (geomShaderSrc != nullptr && *geomShaderSrc != '\0')
    {
        geomShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geomShader, 1, &geomShaderSrc, nullptr);
        glCompileShader(geomShader);

        checkCompileErrors(geomShader, ShaderObjectType::Geometry);
    }

    // Shader program
    this->Id = glCreateProgram();

    glAttachShader(this->Id, vertShader);
    glAttachShader(this->Id, fragShader);
    if (geomShaderSrc != nullptr && *geomShaderSrc != '\0')
        glAttachShader(this->Id, geomShader);

    glLinkProgram(this->Id);

    checkCompileErrors(this->Id, ShaderObjectType::Program);

    // Cleanup
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    if (geomShaderSrc != nullptr && *geomShaderSrc != '\0')
        glDeleteShader(geomShader);
}

void Shader::checkCompileErrors(unsigned int object, ShaderObjectType type)
{
    int success;
    char infoLog[1024];

    if (type != ShaderObjectType::Program)
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, nullptr, infoLog);
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                      << infoLog << "\n -- --------------------------------------------------- -- "
                      << std::endl;
        }
    } else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, nullptr, infoLog);
            std::cout << "| ERROR::SHADER: Link-time error: Type: " << type << "\n"
                      << infoLog << "\n -- --------------------------------------------------- -- "
                      << std::endl;
        }
    }
}
