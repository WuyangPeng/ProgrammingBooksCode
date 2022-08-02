varying vec3 L;
varying vec3 V;
uniform sampler2D texMap;

void main()
{

   vec4 N = texture2D(texMap, gl_TexCoord[0].st);
   vec3 NN =  normalize(2.0*N.xyz-1.0);
   vec3 LL = normalize(L);
  float Kd = max(dot(NN, LL), 0.0);
   gl_FragColor = Kd*gl_FrontLightProduct[0].diffuse;
}
