//=============================================================================
// Shader effect file
//=============================================================================

uniform extern float4x4 matWorld;
uniform extern float4x4 matViewProj;

	
// Define a vertex shader output structure
struct OutputVS
{
    float4 position : POSITION0;
	float2 uv : TEXCOORD0;
	float  shade : TEXCOORD1;
};

// Define the vertex shader program
OutputVS TransformVS(float3 input : POSITION0)
{
    // Zero out our output
	OutputVS output = (OutputVS)0;


    // multiply world with view/proj matrix 
    float4x4 matCombined = mul(matWorld, matViewProj);
	
	// Transform to homogeneous clip space
	output.position = mul(float4(input, 1.0f), matCombined);
	
	 
	// Done--return the output
    return output;
}

// Define the pixel shader program
float4 TransformPS() : COLOR
{
    return float4(0.0f, 0.0f, 0.0f, 1.0f);
}

technique technique1
{
    pass P0
    {
        // Specify the vertex and pixel shader associated with this pass.
        vertexShader = compile vs_2_0 TransformVS();
        pixelShader  = compile ps_2_0 TransformPS();

	// Specify the render/device states associated with this pass.
	FillMode = Wireframe;
    }
}
