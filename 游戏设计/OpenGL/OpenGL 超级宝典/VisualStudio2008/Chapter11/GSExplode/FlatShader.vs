// Cell lighting Shader
// Vertex Shader
// Richard S. Wright Jr.
// OpenGL SuperBible
#version 150

precision highp float;

// Incoming per vertex... position and normal
in vec4 vVertex;
in vec3 vNormal;

uniform vec3 vLightPosition;
uniform mat4 mvpMatrix;
uniform mat4 mvMatrix;
uniform mat3 normalMatrix;

out Fragment
{
    vec4 color;
} fragment;

void main(void)
{
    // Get surface normal in eye coordinates
    vec3 vEyeNormal = normalMatrix * vNormal;

    // Get vertex position in eye coordinates
    vec4 vPosition4 = mvMatrix * vVertex;
    vec3 vPosition3 = vPosition4.xyz / vPosition4.w;

    // Get vector to light source
    vec3 vLightDir = normalize(vLightPosition - vPosition3);

    // Dot product gives us diffuse intensity
    fragment.color = vec4(0.0, 0.0, 0.6, 1.0) * max(0.0, dot(vEyeNormal, vLightDir));

    gl_Position = mvpMatrix * vVertex;
}
