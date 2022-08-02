//--------------------------------------------------------------------------------------
// File: ClipMapPS20.fx
//
// The effect file for the ClipMapPS20 sample.  
// 
//--------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------------------------

texture clipTexture0, clipTexture1, clipTexture2, clipTexture3, clipTexture4;

float4x4 g_mWorld;                  // World matrix for object
float4x4 g_mWorldViewProjection;    // World * View * Projection matrix

#define CLIP_LAYER_COUNT 5

float3 g_clipLayerAndCenter[CLIP_LAYER_COUNT];

//--------------------------------------------------------------------------------------
// Texture samplers
//--------------------------------------------------------------------------------------

sampler clipSamplers[CLIP_LAYER_COUNT] = {
 sampler_state
 {
  texture = <clipTexture0>;
  magfilter = LINEAR;
  minfilter = LINEAR;
  mipfilter = LINEAR;
  AddressU = wrap;
  AddressV = wrap;
 },
 sampler_state
 {
  texture = <clipTexture1>;
  magfilter = LINEAR;
  minfilter = LINEAR;
  mipfilter = LINEAR;
  AddressU = wrap;
  AddressV = wrap;
 },
 sampler_state
 {
  texture = <clipTexture2>;
  magfilter = LINEAR;
  minfilter = LINEAR;
  mipfilter = LINEAR;
  AddressU = wrap;
  AddressV = wrap;
 },
 sampler_state
 {
  texture = <clipTexture3>;
  magfilter = LINEAR;
  minfilter = LINEAR;
  mipfilter = LINEAR;
  AddressU = wrap;
  AddressV = wrap;
 },
 sampler_state
 {
  texture = <clipTexture4>;
  magfilter = LINEAR;
  minfilter = LINEAR;
  mipfilter = LINEAR;
  AddressU = wrap;
  AddressV = wrap;
 },
};


//--------------------------------------------------------------------------------------
// Vertex shader output structure
//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Position   : POSITION;   // vertex position 
    float2 TextureUV[CLIP_LAYER_COUNT]  : TEXCOORD0;  // vertex texture coords 
};


//--------------------------------------------------------------------------------------
// This shader computes standard transform and lighting
//--------------------------------------------------------------------------------------
VS_OUTPUT RenderSceneVS( float4 vPos : POSITION, 
                         float3 vNormal : NORMAL,
                         float2 vTexCoord0 : TEXCOORD0)
{
    VS_OUTPUT Output;
    float3 vNormalWorldSpace;
      
    // Transform the position from object space to homogeneous projection space
    Output.Position = mul(vPos, g_mWorldViewProjection);
    
    // Transform the normal from object space to world space    
    vNormalWorldSpace = normalize(mul(vNormal, (float3x3)g_mWorld)); // normal (world space)

	// Copy the texture coordinate through.
	for(int i=0; i<CLIP_LAYER_COUNT; i++)
		Output.TextureUV[i] = vTexCoord0.xy * g_clipLayerAndCenter[i].z;
		
    return Output;    
}


//--------------------------------------------------------------------------------------
// Pixel shader output structure
//--------------------------------------------------------------------------------------
struct PS_OUTPUT
{
    float4 RGBColor : COLOR0;  // Pixel color    
};


//--------------------------------------------------------------------------------------
// This shader outputs the pixel's color by modulating the texture's
//       color with diffuse material color
//--------------------------------------------------------------------------------------
PS_OUTPUT RenderScenePS( VS_OUTPUT In ) 
{ 
    PS_OUTPUT Output;

	// The base level can always be sampled as there's nothing behind it...
	// so save some math.
    float3 colAccum = tex2D(clipSamplers[0], In.TextureUV[0]);
    
    // Grab the rest, fading based on distance from each layer's center.
    for(int i=1; i<CLIP_LAYER_COUNT; i++)
    {
       float fade = smoothstep(0.4, 0.5, distance(In.TextureUV[i], g_clipLayerAndCenter[i].xy));
       float4 curColor = tex2D(clipSamplers[i], In.TextureUV[i]); //In.TextureUV[i].xyxy;
       colAccum = lerp(curColor, colAccum, fade);
    }
    
    // Store accumulated result and return.
    Output.RGBColor = float4(colAccum,1); //In.TextureUV[0].xyxy;
    return Output;
}


//--------------------------------------------------------------------------------------
// Render mesh using clipmap.
//--------------------------------------------------------------------------------------
technique RenderClipMapPS2
{
    pass P0
    {
        VertexShader = compile vs_2_0 RenderSceneVS();
        PixelShader  = compile ps_2_0 RenderScenePS();
    }
}

