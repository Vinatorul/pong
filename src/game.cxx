#include "game.hxx"

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include <string>
#include <vector>
#include <iostream> 
#include <fstream>
#include "rect.hxx"

Game::Game(SDL_Window* __w, SDL_GLContext __c) :
    window(__w),
    glcontext(__c),
    t_matrix({
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 
        0.0f, 0.0f, 1.0f, 0.0f, 
        0.0f, 0.0f, 0.0f, 1.0f
    }),
    rect(0,0,0,0)
{  
    program_id = 0;
    vertex_shader_filename = "src/shaders/330es.vert";
    fragment_shader_filename = "src/shaders/330es.frag";
}

void Game::load_shaders() {
    GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

    GLint result = GL_FALSE;
    int info_len;

    // compile and check vertex shader
    std::ifstream vertex_shader_fs(vertex_shader_filename);
    std::string vertex_shader((std::istreambuf_iterator<char>(vertex_shader_fs)),
                               std::istreambuf_iterator<char>());
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
    std::ifstream fragment_shader_fs(fragment_shader_filename);
    std::string fragment_shader((std::istreambuf_iterator<char>(fragment_shader_fs)),
                                 std::istreambuf_iterator<char>());
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

    program_id = glCreateProgram();
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
}

void Game::run() {
    load_shaders();

    GLuint vertex_array_id;
    glGenVertexArrays(1, &vertex_array_id);
    glBindVertexArray(vertex_array_id);
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, rect.mesh_size(), rect.get_mesh(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    t_matrix_location = glGetUniformLocation(program_id, "tmatrix");
    // t_matrix[12]  = 0.2f;
    // t_matrix[13]  = 0.2f;
    t_matrix[0] = 0.1f;
    t_matrix[5] = 0.1f;

    SDL_Event e;
    bool quit = false;
    int start_time = 0;
    int end_time = 0;
    int delta = 0;
    int fps = 60;
    int time_per_frame = 16; // miliseconds
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        update();
        end_time = SDL_GetTicks();
        delta = end_time - start_time;
        if (delta >= time_per_frame) {
            fps = 1000 / delta;
            draw();
            start_time = end_time;
        }
        // std::cerr << "FPS is: " << fps << std::endl;
    }
}


void Game::draw() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    
    glUseProgram(program_id);

    rect.apply_transform(t_matrix);
    rect.update();
    glUniformMatrix4fv (t_matrix_location, 1, GL_FALSE, t_matrix);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDisableVertexAttribArray(0);
    glUseProgram(0);

    SDL_GL_SwapWindow(window);
}

void Game::update() {
}