#include "game.hxx"

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include <string>
#include <vector>
#include <iostream> 

Game::Game(SDL_Window* __w, SDL_GLContext __c) :
    window(__w),
    glcontext(__c) {  
}

std::string vertex_shader = "#version 300 es\n"
                           "in vec3 pos;"
                           "void main() {"
                           "gl_Position = vec4(pos, 1);"
                           "}"; 
  
std::string fragment_shader = "#version 300 es\n"
                            "#undef lowp\n"
                            "#undef mediump\n"
                            "#undef highp\n"
                            "precision mediump float;\n"
                             "out vec4 fragmentColor;"
                             "void main() {"
                             "fragmentColor = vec4(1.0, 0.0, 0.0, 1.0);"
                             "}"; 


GLuint load_shaders() {
    GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

    GLint result = GL_FALSE;
    int info_len;

    // compile and check vertex shader
    char const * p_vertex_shader = vertex_shader.c_str();
    glShaderSource(vertex_shader_id, 1, &p_vertex_shader , NULL);
    glCompileShader(vertex_shader_id);
    glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertex_shader_id, GL_INFO_LOG_LENGTH, &info_len);
    if (info_len > 1) {
        std::vector<char> error_msg(info_len+1);
        glGetShaderInfoLog(vertex_shader_id, info_len, NULL, &error_msg[0]);
        std::cout << &error_msg[0] << std::endl;
    }

    // compile and check fragment shader
    char const * p_fragment_shader = fragment_shader.c_str();
    glShaderSource(fragment_shader_id, 1, &p_fragment_shader , NULL);
    glCompileShader(fragment_shader_id);
    glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragment_shader_id, GL_INFO_LOG_LENGTH, &info_len);
    if (info_len > 1) {
        std::vector<char> error_msg(info_len+1);
        glGetShaderInfoLog(fragment_shader_id, info_len, NULL, &error_msg[0]);
        std::cout << &error_msg[0] << std::endl;
    }

    GLuint program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);
    glLinkProgram(program_id);
    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_len);
    if (info_len > 1) {
        std::vector<char> error_msg(info_len+1);
        glGetProgramInfoLog(program_id, info_len, NULL, &error_msg[0]);
        std::cout << &error_msg[0] << std::endl;
    }

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    return program_id;
}

void Game::run() {


    GLuint program_id = load_shaders();

    glDisableVertexAttribArray(0);
    glUseProgram(program_id);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    GLuint vertex_array_id;
    glGenVertexArrays(1, &vertex_array_id);
    glBindVertexArray(vertex_array_id);
    static const GLfloat g_vertex_buffer_data[] = {
       -1.0f, -1.0f, 0.0f,
       1.0f, -1.0f, 0.0f,
       0.0f,  1.0f, 0.0f,
    };  
    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexAttribPointer(
       0,                  
       3,                  
       GL_FLOAT,           
       GL_FALSE,           
       0,                  
       (void*)0            
    );
    glDrawArrays(GL_TRIANGLES, 0, 3);

    SDL_GL_SwapWindow(window);
    SDL_Delay(2000);
}