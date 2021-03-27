#define GL_GLEXT_PROTOTYPES
#define GL_SILENCE_DEPRECATION
#define SDL_MAIN_HANDLED

#ifdef _WIN32
#include <glew.h>
#else

#include <SDL_opengl.h>

#endif

#include <SDL.h>
#include <iostream>
#include "game.h"
#include "resource_manager.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

bool closeWindow = false;
SDL_Window *window;
SDL_GLContext glContext;

Game game(SCREEN_WIDTH, SCREEN_HEIGHT);

int main()
{
    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    }

    // Use the most recent OpenGL Version available in the machine
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
#ifdef __APPLE__
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#endif

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

    // GLEW init
#ifdef _WIN32
    GLenum glewError = glewInit();
    if(glewError != GLEW_OK)
        std::cout << "Error initializing GLEW!" << std::endl;
#endif

    // OpenGL configuration
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // Print versions
    SDL_version sdlVersion;
    SDL_GetVersion(&sdlVersion);
    std::cout << "SDL Version: " << unsigned(sdlVersion.major) << "." << unsigned(sdlVersion.minor) << "."
              << unsigned(sdlVersion.patch)
              << std::endl;

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    // Init game
    game.init();

    // Delta Time
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    // Window loop
    while (!closeWindow)
    {
        // Calculate delta time
        float currentFrame = SDL_GetTicks();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Game input
        game.processInput(deltaTime);

        // Game update
        game.update(deltaTime);

        // Game render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        game.render();

        // Process inputs
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // Close window when clicking the "X" button
            if (event.type == SDL_QUIT)
                closeWindow = true;

            // Close window when pressing escape
            if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                closeWindow = true;

            // REVIEW: Might be wrong
            if (event.key.keysym.scancode >= 0)
            {
                if (event.type == SDL_KEYDOWN)
                    game.keys[event.key.keysym.scancode] = true;
                else if (event.type == SDL_KEYUP)
                    game.keys[event.key.keysym.scancode] = false;
            }
        }

        // Swap buffers and present to the screen
        SDL_GL_SwapWindow(window);
    }

    // Cleanup resources
    ResourceManager::Clear();

    // Cleanup variables used
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    // Closes the application
    return EXIT_SUCCESS;
}

#ifdef _WIN32
void WinMain()
{
    main();
}
#endif
