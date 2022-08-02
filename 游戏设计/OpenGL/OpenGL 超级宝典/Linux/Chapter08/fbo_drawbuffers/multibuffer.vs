#version 150 
// multibuffer.vs
// transform incoming verticies, 
// output vertex color and tex coords


in vec3 vVertex;
in vec3 vNormal;
in vec2 texCoord0;

uniform mat4 mvMatrix;
uniform mat4 pMatrix;
uniform vec3 vLightPos;
uniform vec4 vColor;

out vec4 vFragColor;
out vec2 vTexCoord;

void main(void) 
{ 
	mat3 mNormalMatrix;
	mNormalMatrix[0] = normalize(mvMatrix[0].xyz);
	mNormalMatrix[1] = normalize(mvMatrix[1].xyz);
	mNormalMatrix[2] = normalize(mvMatrix[2].xyz);
	
	vec3 vNorm = normalize(mNormalMatrix * vNormal);
	
	vec4 ecPosition;
	vec3 ecPosition3;
	ecPosition = mvMatrix * vec4(vVertex, 1.0);
	ecPosition3 = ecPosition.xyz /ecPosition.w;
	vec3 vLightDir = normalize(vLightPos - ecPosition3);
	float fDot = max(0.0, dot(vNorm, vLightDir)); 
	vFragColor.rgb = vColor.rgb * fDot;
	vFragColor.a = vColor.a;
	vTexCoord = texCoord0;
	mat4 mvpMatrix;
	mvpMatrix = pMatrix * mvMatrix;
	gl_Position = mvpMatrix * vec4(vVertex, 1.0); 
}
