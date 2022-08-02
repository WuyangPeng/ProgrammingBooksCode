void main()
{
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec4 eyePosition = gl_ModelViewMatrix * gl_Vertex;
    vec4 eyeLightPos = gl_LightSource[0].position;
    vec3 eyeNormalVec = normalize(gl_NormalMatrix * gl_Normal);
    vec3 eyeLightVec = normalize(eyeLightPos.xyz - eyePosition.xyz);
    vec3 eyeViewVec = -normalize(eyePosition.xyz);
    vec3 eyeHalfVec = normalize(eyeLightVec + eyeViewVec);
    float Kd = max(dot(eyeLightVec, eyeNormalVec), 0.0);
    float Ks = pow(max(dot(eyeNormalVec, eyeHalfVec), 0.0), gl_FrontMaterial.shininess);
    float Ka = 0.0;

    ambient = Ka*gl_FrontLightProduct[0].ambient;
    diffuse = Kd*gl_FrontLightProduct[0].diffuse;
    specular = Ks*gl_FrontLightProduct[0].specular;
    gl_FrontColor = ambient+diffuse+specular;
}
