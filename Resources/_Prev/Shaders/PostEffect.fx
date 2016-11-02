
float pixelSizeU;
float pixelSizeV;
float pixelHalfSizeU;
float pixelHalfSizeV;


//Sampler
texture screenTex;
sampler2D screenSampler = sampler_state{
	Texture = screenTex;
	
};

struct VS_INPUT{
	float4 pos : POSITION;
	float2 uv : TEXCOORD0;
};

struct VS_OUTPUT{
	float4 pos : POSITION;
	float2 uv : TEXCOORD0;
};


VS_OUTPUT vs_Base( VS_INPUT Input )
{
	VS_OUTPUT Output;
	Output.pos = Input.pos;
	Output.uv = Input.uv;

	return Output;
}


float4 ps_Base( VS_OUTPUT Input ) : COLOR0
{
	Input.uv.x -= pixelHalfSizeU;
	Input.uv.y -= pixelHalfSizeV;

	return tex2D( screenSampler, Input.uv );
}


technique Base
{
    pass p0
    {
        VertexShader = compile vs_3_0 vs_Base();
        PixelShader = compile ps_3_0 ps_Base();
    }
}