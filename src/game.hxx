#ifndef __GAME_HXX__
#define __GAME_HXX__

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

class Game {
private:
    SDL_Window *window;
    SDL_GLContext glcontext;
public:
    Game(SDL_Window* __w, SDL_GLContext __c);

    void run();
};

#endif
