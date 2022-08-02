void main()
{
    const vec4 yellow = vec4(1.0, 1.0, 0.0, 1.0);
    const vec4 red = vec4(1.0, 0.0, 0.0, 1.0);
    const vec4 black = vec4(0.0, 0.0, 0.0, 1.0);

    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec4 eyePosition = gl_ModelViewMatrix * gl_Vertex;
    vec4 eyeLightPos = gl_LightSource[0].position;
    vec3 N = normalize(gl_NormalMatrix * gl_Normal);
    vec3 L = normalize(eyeLightPos.xyz - eyePosition.xyz);
    vec3 E = -normalize(eyePosition.xyz);
    vec3 H = normalize(L + E);
    float Kd = max(dot(L, N), 0.0);
    float Ks = pow(max(dot(N, H), 0.0), gl_FrontMaterial.shininess);
    float Ka = 0.0;

    ambient = Ka*gl_FrontLightProduct[0].ambient;
    diffuse = Kd*gl_FrontLightProduct[0].diffuse;
    specular = Ks*gl_FrontLightProduct[0].specular;
    if(Kd > 0.6) diffuse = yellow;
      else diffuse = red;
    gl_FrontColor = diffuse;
    if(abs(dot(E,N))<0.25) gl_FrontColor = black;
}
