//=============================================================================
// Basic ambient and diffuse lighting. Adapted from shader by Frank Luna.
//=============================================================================

uniform extern float4x4 gWVP;
uniform extern float4x4 gWorldInverseTranspose;
uniform extern float4 gAmbientMtrl;
uniform extern float4 gAmbientLight;
uniform extern float4 gDiffuseMtrl;
uniform extern float4 gDiffuseLight;
uniform extern float3 gLightVecW;
 
struct OutputVS
{
    float4 position  : POSITION0;
    float4 color : COLOR0;
};

OutputVS AmbientDiffuseVS(float3 input : POSITION0, float3 normalL : NORMAL0)
{
	OutputVS outVS = (OutputVS)0;
	
	//the usual world/view/proj transform
	outVS.position = mul(float4(input, 1.0f), gWVP);
	

	//calculate normal for the diffuse light
	float3 normalW = mul(float4(normalL, 0.0f), gWorldInverseTranspose).xyz;
	normalW = normalize(normalW);
	
	//calculate diffuse color based on light direction
	float s = max(dot(gLightVecW, normalW), 0.0f);
	float3 diffuse = s * (gDiffuseMtrl * gDiffuseLight).rgb;

	//calculate ambient color	
	float3 ambient = gAmbientMtrl * gAmbientLight;
	
	//combine ambient and diffuse colors for final output color
	outVS.color.rgb = ambient + diffuse;
	
	//copy the alpha level
	outVS.color.a   = gDiffuseMtrl.a;
	

    return outVS;
}

float4 AmbientDiffusePS(float4 c : COLOR0) : COLOR
{
    return c;
}

technique technique1
{
    pass P0
    {
        vertexShader = compile vs_2_0 AmbientDiffuseVS();
        pixelShader  = compile ps_2_0 AmbientDiffusePS();
    }
}
