#version 450

#include "fragment.glsl"

void main() {
    COLOR = fragmentColor(vec4(fs_in.UV.x, fs_in.UV.y, 1.0, 1.0), true);
}
