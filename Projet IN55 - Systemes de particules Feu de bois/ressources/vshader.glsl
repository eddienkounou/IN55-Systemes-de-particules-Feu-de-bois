#version 330

uniform mat4 mvp;

in vec3 position;
in vec3 color;

out vec3 fColor;

//! [0]
void main()
{
    // Calculate vertex position in screen space
    gl_Position = mvp * vec4( position, 1.0 );

    fColor = color;
}
//! [0]
