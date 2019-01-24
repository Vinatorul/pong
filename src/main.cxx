#include <iostream>


#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "game.hxx"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    } else {
        SDL_Window *window = SDL_CreateWindow("Vinatorul/pong", 
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SCREEN_WIDTH,
                                  SCREEN_HEIGHT,
                                  SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
        if (!window) {
            std::cout << "Window could not be created! SDL_Error:" << SDL_GetError() << std::endl;
        }
        else {
            SDL_GLContext glcontext = SDL_GL_CreateContext(window);
            if (!glcontext) {
                std::cout << "OpenGL context could not be created! SDL_Error:" << SDL_GetError() << std::endl;             
            } else {
                std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
                GLenum err = glewInit();
                if (err != GLEW_OK) {
                    std::cout << "GLEW could not be initialized! Error: " << err << std::endl;
                } else {
                    Game game(window, glcontext);
                    game.run();
                }
            }
            SDL_GL_DeleteContext(glcontext); 
        }
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
    return 0;
}
