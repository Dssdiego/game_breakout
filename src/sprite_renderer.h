//
// Created by Diego Santos Seabra on 27/03/21.
//

#ifndef BREAKOUT_SPRITE_RENDERER_H
#define BREAKOUT_SPRITE_RENDERER_H

#include "shader.h"
#include "texture.h"

class SpriteRenderer
{
public:
    SpriteRenderer(Shader &shader);
    ~SpriteRenderer();

    void drawSprite(Texture2D texture2D, glm::vec2 position,
                    glm::vec2 size = glm::vec2(10.0f, 10.0f),
                    float rotate = 0.0f,
                    glm::vec3 color = glm::vec3(1.0f));
private:
    Shader shader;
    unsigned int quadVAO;

    void initRenderData();
};


#endif //BREAKOUT_SPRITE_RENDERER_H
