//
// Created by Diego Santos Seabra on 26/03/21.
//

#include <glm/ext.hpp>
#include "game.h"
#include "sprite_renderer.h"
#include "resource_manager.h"

SpriteRenderer *spriteRenderer;

Game::Game(unsigned int width, unsigned int height) : state(ACTIVE), keys(), width(width), height(height)
{}

Game::~Game()
{

}

void Game::init()
{
    // Load shaders
    Shader spriteShader = ResourceManager::LoadShader("assets/shaders/sprite.glsl", "sprite");

    // Configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->width),
                                      static_cast<float>(this->height), 0.0f,
                                      -1.0f, 1.0f);
    spriteShader
            .Use()
            .SetInteger("image", 0)
            .SetMatrix4("projection", projection);
    // TODO: Make all shader methods return the shader itself,
    //  making able to concatenate operations, just like above

    spriteRenderer = new SpriteRenderer(spriteShader);
    // TODO: Make shader inside sprite renderer? Check examples of other game engines

    // Load textures
    ResourceManager::LoadTexture("assets/textures/awesomeface.png", true, "face");
}

void Game::processInput(float deltaTime)
{

}

void Game::update(float deltaTime)
{

}

void Game::render()
{
    spriteRenderer->drawSprite(ResourceManager::GetTexture("face"),
                               glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 300.0f),
                               0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    // TODO: Create color class
    // TODO: Create transform class
}
