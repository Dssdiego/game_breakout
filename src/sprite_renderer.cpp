//
// Created by Diego Santos Seabra on 27/03/21.
//

#define GL_GLEXT_PROTOTYPES
#define GL_SILENCE_DEPRECATION

#include "sprite_renderer.h"

#ifdef _WIN32
#include <glew.h>
#else
#include <SDL_opengl.h>
#include <SDL_opengl_glext.h>
#include <glm/ext.hpp>

#endif

SpriteRenderer::SpriteRenderer(Shader &shader)
{
    this->shader = shader;
    this->initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
    glDeleteVertexArrays(1, &this->quadVAO);
}

void SpriteRenderer::initRenderData()
{
    // Configure VAO/VBO
    unsigned int vbo;

    float vertices[] = {
            // position //texture
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,

            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f
    }; // (0,0) being top-left corner of the quad

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);       // bind
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind
    glBindVertexArray(0);
}

void SpriteRenderer::drawSprite(Texture2D texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color)
{
    // Prepare transformations
    this->shader.Use();
    glm::mat4 model = glm::mat4(1.0f);

    // Put origin of the model in the center
    model = glm::translate(model, glm::vec3(position, 0.0f));

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

    model = glm::scale(model, glm::vec3(size, 1.0f));

    // Pass properties to the shader
    this->shader.SetMatrix4("model", model);
    this->shader.SetVector3f("spriteColor", color);

    // Bind/draw/unbind
    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
