#include <SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

bool closeWindow = false;
SDL_Window *window;
SDL_GLContext glContext;

int main()
{
    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    }

    // Create window
    window = SDL_CreateWindow(
            "Breakout",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            SCREEN_WIDTH, SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
    );

    // If there is any error creating the window
    if (!window)
    {
        std::cout << "Failed to create window! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }

    // OpenGL Context
    glContext = SDL_GL_CreateContext(window);

    // VSync
//    SDL_GL_SetSwapInterval(1);

    // Window current context
    SDL_GL_MakeCurrent(window, glContext);

    // Window loop
    while(!closeWindow) {
        SDL_Event event;

        // Process inputs
        while(SDL_PollEvent(&event))
        {
            // Close window when clicking the "X" button
            if (event.type == SDL_QUIT)
            {
                closeWindow = true;
            }

            // Close window when pressing escape
            if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
            {
                closeWindow = true;
            }
        }

        // Swap buffers and present to the screen
        SDL_GL_SwapWindow(window);
    }

    // Cleanup variables used
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    // Closes the application
    return EXIT_SUCCESS;
}