//============================================================================
//
// Listing 7.2
//
// Mathematics for 3D Game Programming and Computer Graphics, 3rd ed.
// By Eric Lengyel
//
// The code in this file may be freely used in any software. It is provided
// as-is, with no warranty of any kind.
//
//============================================================================


in vec4				vertexPosition;		// The object-space vertex position.
in vec3				normal;				// The object-space vertex normal.
in vec4				tangent;			// The object-space vertex tangent.
out vec3			view;				// The tangent-space view direction.
out vec3			light;				// The tangent-space light direction.
uniform vec4		mvpMatrix[4];		// The model-view-projection matrix.
uniform vec3		cameraPosition;		// The object-space camera position.
uniform vec3		lightDirection;		// The object-space light direction.

void main()
{
	// Transform the vertex into clip space.
	gl_Position = vec4(dot(mvpMatrix[0], vertexPosition),
			dot(mvpMatrix[1], vertexPosition),
			dot(mvpMatrix[2], vertexPosition),
			dot(mvpMatrix[3], vertexPosition));
	
	// Calculate the bitangent B = (N x T) * T.w.
	vec3 bitangent = cross(normal, tangent.xyz) * tangent.w;
	
	// Transform V into tangent space.
	view = cameraPosition - vertexPosition;
	view = vec3(dot(tangent, view), dot(bitangent, view),
			dot(normal, view));
	
	// Transform L into tangent space.
	light = vec3(dot(tangent, lightDirection),
			dot(bitangent, lightDirection), dot(normal, lightDirection));
}
