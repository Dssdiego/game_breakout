//
// Created by Diego Santos Seabra on 26/03/21.
//

#define GL_GLEXT_PROTOTYPES
#define GL_SILENCE_DEPRECATION

#ifdef _WIN32
#include <glew.h>
#else
#include <SDL_opengl.h>
#endif

#include "texture.h"

Texture2D::Texture2D()
        : Width(0), Height(0), InternalFormat(GL_RGB), ImageFormat(GL_RGB), WrapS(GL_REPEAT), WrapT(GL_REPEAT),
          FilterMin(GL_LINEAR), FilterMax(GL_LINEAR)
{
    glGenTextures(1, &this->Id);
}

void Texture2D::Generate(unsigned int width, unsigned int height, unsigned char *data)
{
    this->Width = width;
    this->Height = height;

    // Create texture
    glBindTexture(GL_TEXTURE_2D, this->Id);
    glTexImage2D(GL_TEXTURE_2D, 0, this->InternalFormat, width, height, 0, this->ImageFormat, GL_UNSIGNED_BYTE, data);

    // Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->WrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->WrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->FilterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->FilterMax);

    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, this->Id);
}
