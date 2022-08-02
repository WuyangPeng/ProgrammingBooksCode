This directory contains separate directories for each shader application.
Windows users should add the GLEW library as indicated in a previous README
and us the parameter "rb" rather than "r" in fopen. The directories contain
the following applications:

WAVE: the example in the text which display a time varying mesh with line loops.

WAVE2: the wave example with a solid mesh and lighting,

PHONG: This directory contains a phong vertex shaderi application, a modified phone vertex
shader application,  a modified phone fragment shader application and the corresponding
vertex and fragment shaders.

MORPH: contains an application that uses a vertex shader to morph a triangle into
another triangle

PARTICLE: a very simple particle system that uses the shader to computer particle
posiitons

NONPHOTO: Cartoon shader example

CUBE MAP: textures mapping using a reflection map in the fragment shader.
The cubemap textures is simply a box with each side a different color.

BUMBMAP: Simple bump mapping example with a rotating light source. The
height map is simply a square inside another square.
