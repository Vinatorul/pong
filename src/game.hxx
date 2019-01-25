#ifndef __GAME_HXX__
#define __GAME_HXX__

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <string>

class Game {
private:
    SDL_Window *window;
    SDL_GLContext glcontext;
    GLuint program_id;
    std::string vertex_shader_filename;
    std::string fragment_shader_filename;

    void load_shaders();
    void update();
    void draw();
public:
    Game(SDL_Window* __w, SDL_GLContext __c);

    void run();
};

#endif
