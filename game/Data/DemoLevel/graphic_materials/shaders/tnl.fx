// Textures
texture gmp_texture1;

// Matrices
float4x4 gmp_view;
float4x4 gmp_projection;
float4x4 gmp_world;
float4x4 gmp_wvp;

sampler TextureSampler = sampler_state {
    Texture = <gmp_texture1>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

struct VS_OUTPUT {
    float4 Position: POSITION;
    float4 Diffuse: COLOR0;
    float2 TextureUV: TEXCOORD0;
};

struct PS_OUTPUT {
    float4 RGBColor: COLOR0;
};

VS_OUTPUT RenderSceneVS(float4 pos: POSITION, float3 normal: NORMAL, float2 texCoord0: TEXCOORD0) {
    VS_OUTPUT Output;

	Output.Position = mul(pos, gmp_wvp);
    Output.Diffuse.rgb = float3(1.0f, 1.0f, 1.0f);
    Output.Diffuse.a = 1.0f;
    Output.TextureUV = texCoord0;

    return Output;    
}

PS_OUTPUT RenderScenePS(VS_OUTPUT In, uniform bool bTexture)  { 
    PS_OUTPUT Output;

    if(bTexture) {
        Output.RGBColor = tex2D(TextureSampler, In.TextureUV);
    } else {
		Output.RGBColor = In.Diffuse;
	}

    return Output;
}

technique RenderScene {
    pass P0 {          
		AlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;
        VertexShader = compile vs_2_0 RenderSceneVS();
        PixelShader  = compile ps_2_0 RenderScenePS(true);
    }
}