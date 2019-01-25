#version 300 es

#undef lowp
#undef mediump
#undef highp
precision mediump float;

out vec4 fragmentColor;

void main() {
    fragmentColor = vec4(1.0, 0.0, 0.0, 1.0);
}
