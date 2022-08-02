//============================================================================
//
// Listing 10.2
//
// Mathematics for 3D Game Programming and Computer Graphics, 3rd ed.
// By Eric Lengyel
//
// The code in this file may be freely used in any software. It is provided
// as-is, with no warranty of any kind.
//
//============================================================================


in vec4				vertexPosition;		// The object-space vertex position.
uniform vec4		mvpMatrix[4];		// The model-view-projection matrix.
uniform vec3		lightPosition;		// The object-space light position.

void main()
{
	float t = (vertexPosition.w < 0.5) ? 1.0 : 0.0;
	vec4 extrudedPosition = vec4(vertexPosition.xyz - lightPosition * t,
										vertexPosition.w);

	gl_Position = vec4(dot(mvpMatrix[0], extrudedPosition),
			dot(mvpMatrix[1], extrudedPosition),
			dot(mvpMatrix[2], extrudedPosition),
			dot(mvpMatrix[3], extrudedPosition));
}
