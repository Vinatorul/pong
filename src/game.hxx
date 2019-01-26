#ifndef __GAME_HXX__
#define __GAME_HXX__

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <string>
#include <vector>
#include <GL/gl.h>
#include "rect.hxx"

class Game {
private:
    SDL_Window *window;
    SDL_GLContext glcontext;
    GLuint program_id;
    std::string vertex_shader_filename;
    std::string fragment_shader_filename;
    std::vector<Rect> rects;
    GLuint vertex_buffer;
    GLint t_matrix_location;
    GLfloat t_matrix[16]; 
    Rect rect;

    void load_shaders();
    void update();
    void draw();
public:
    Game(SDL_Window* __w, SDL_GLContext __c);

    void run();
};

#endif
