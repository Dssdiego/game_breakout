//
// Created by Diego Santos Seabra on 26/03/21.
//

#ifndef BREAKOUT_GAME_H
#define BREAKOUT_GAME_H

enum GameState
{
    ACTIVE,
    MENU,
    WIN
};

class Game
{
public:
    GameState state;
    bool keys[512]; // SDL has 512 scancode keys (see at "SDL_keycode.h")
    unsigned int width, height;

    Game(unsigned int width, unsigned int height);
    ~Game();

    void init();
    void processInput(float deltaTime);
    void update(float deltaTime);
    void render();
};

#endif //BREAKOUT_GAME_H
