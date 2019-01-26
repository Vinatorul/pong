#version 300 es

in vec3 pos;
uniform mat4 tmatrix;

void main() {
    vec3 t_pos = pos;
    t_pos.x = t_pos.x * 3.0f/4.0f;
    gl_Position = tmatrix * vec4(t_pos, 1.0);
}
