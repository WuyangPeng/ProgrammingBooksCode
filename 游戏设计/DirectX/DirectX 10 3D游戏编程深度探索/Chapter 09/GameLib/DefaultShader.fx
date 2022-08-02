/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

matrix g_mtxWorld;
matrix g_mtxView;
matrix g_mtxProj;

#define MAX_LIGHTS 10	// Ensure this is the same as the C++ value

int4  g_viLightStatus;
float4 g_vLightColors[MAX_LIGHTS];
float4 g_vLightDirections[MAX_LIGHTS];

int4 g_viTextureStatus;
Texture2D g_Textures[8];

////////////////////////////////////////////////////////////////////////////
// Default Vertex Shader
struct VS_INPUT
{
    float3 vPosition	: POSITION;
    float3 vNormal		: NORMAL;
    float4 vColor		: COLOR0;
    float2 vTexCoords1	: TEXCOORD;
    float2 vTexCoords2	: TEXCOORD;
};

struct VS_OUTPUT
{
	float4 vPosition	: SV_POSITION;
	float3 vNormal		: NORMAL;
    float4 vColor		: COLOR0;
    float2 vTexCoords1	: TEXCOORD0;
    float2 vTexCoords2	: TEXCOORD1;
};

VS_OUTPUT DefaultVS(VS_INPUT dataIn) 
{
    VS_OUTPUT result;
    
    float4 vPos = float4(dataIn.vPosition, 1.0f);
    
    float4 vFinalPos = mul(vPos, g_mtxWorld);
    vFinalPos = mul(vFinalPos, g_mtxView);
    vFinalPos = mul(vFinalPos, g_mtxProj);
    
    result.vPosition = vFinalPos;
    result.vNormal = dataIn.vNormal;
    result.vColor = dataIn.vColor;   
    result.vTexCoords1 = dataIn.vTexCoords1; 
    result.vTexCoords2 = dataIn.vTexCoords2; 
    
    return result;
}

////////////////////////////////////////////////////////////////////////////
// Default Pixel Shader 

SamplerState SamplerStateWrap
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};


float4 DefaultPS(VS_OUTPUT dataIn) : SV_Target
{
	float4 finalColor = dataIn.vColor;   

	if(g_viLightStatus.x > 0)
	{
		for(int iCurLight = 0 ; iCurLight < g_viLightStatus.x ; iCurLight++)
		{
			finalColor += saturate(dot(g_vLightDirections[iCurLight], dataIn.vNormal) * g_vLightColors[iCurLight]);
		}
	}
	
	float4 texColor = finalColor;
	
	if(g_viTextureStatus.x > 0)
		texColor *= g_Textures[0].Sample(SamplerStateWrap, dataIn.vTexCoords1);
	if(g_viTextureStatus.x > 1)
		texColor *= (g_Textures[1].Sample(SamplerStateWrap, dataIn.vTexCoords2));
	
	return texColor;
}

////////////////////////////////////////////////////////////////////////////
// Default Technique
technique10 DefaultTechnique
{
    pass Pass0
    {
		SetGeometryShader(NULL);
        SetVertexShader(CompileShader(vs_4_0, DefaultVS()));
        SetPixelShader(CompileShader(ps_4_0, DefaultPS()));
    }    
}


VS_OUTPUT MT_VS(VS_INPUT dataIn) 
{
    VS_OUTPUT result;
    
    float4 vPos = float4(dataIn.vPosition, 1.0f);
    
    float4 vWorldPos = mul(vPos, g_mtxWorld);
    float4 vViewPos = mul(vWorldPos, g_mtxView);
    float4 vScreenPos = mul(vViewPos, g_mtxProj);
    
    result.vPosition = vScreenPos;
    result.vColor = dataIn.vColor;   
    result.vTexCoords1 = dataIn.vTexCoords1; 
    
    float3 vViewNormal = normalize(mul(mul(dataIn.vNormal, g_mtxWorld), g_mtxView));    
    
    result.vNormal = vViewNormal;
    
    float3 vReflection = normalize(reflect(vViewPos, vViewNormal));
    
    float fTemp = 2.0f * sqrt(
		vReflection.x * vReflection.x + 
		vReflection.y * vReflection.y +
		(vReflection.z+1.0f) * (vReflection.z+1.0f)
		);
    
    result.vTexCoords2.x = vReflection.x / fTemp + 0.5f;
    result.vTexCoords2.y = vReflection.y / fTemp + 0.5f;    
     
    return result;
}

float4 MT_PS(VS_OUTPUT dataIn) : SV_Target
{
	float4 diffuseColor = 0;
	
	float3 vLightDir = float3(-1,0.0,-0.2);
	float4 vSunColor = float4(1,0.8,0.4,0);
	
	diffuseColor = saturate(dot(vLightDir, dataIn.vNormal) * vSunColor);
	
	float4 baseColor = g_Textures[0].Sample(SamplerStateWrap, dataIn.vTexCoords1);	
	float4 detailColor = g_Textures[2].Sample(SamplerStateWrap, dataIn.vTexCoords1);
	float4 envColor = g_Textures[5].Sample(SamplerStateWrap, dataIn.vTexCoords2);
	float4 glowColor = g_Textures[1].Sample(SamplerStateWrap, dataIn.vTexCoords1);
	float4 maskColor = g_Textures[6].Sample(SamplerStateWrap, dataIn.vTexCoords1);
	float4 cloudColor = g_Textures[7].Sample(SamplerStateWrap, dataIn.vTexCoords1);
	float4 glossColor = g_Textures[4].Sample(SamplerStateWrap, dataIn.vTexCoords1);
	
	glossColor = pow(glossColor * diffuseColor, 4) * 4;
	baseColor = (baseColor * detailColor * diffuseColor);
	envColor = envColor * (1-maskColor) * 0.3f;	
	glowColor = pow(glowColor * (1-diffuseColor), 4);
	
	float4 finalColor = baseColor + envColor + glowColor + glossColor;
	
	return finalColor + (cloudColor* 0.5f);
}

technique10 MultiTexTechnique
{
    pass PassBackground
    {
		SetGeometryShader(NULL);
        SetVertexShader(CompileShader(vs_4_0, MT_VS()));
        SetPixelShader(CompileShader(ps_4_0, MT_PS()));
    }    
}












