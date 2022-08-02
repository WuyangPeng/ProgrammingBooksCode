// Starfield Shader
// Fragment Shader
// Richard S. Wright Jr.
// OpenGL SuperBible
#version 130

out vec4 vFragColor;

uniform sampler2D  starImage;

void main(void)
    { 
    vFragColor = texture(starImage, gl_PointCoord);
    }
    