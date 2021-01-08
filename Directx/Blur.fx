texture texTexture;
sampler sampTexture = sampler_state {
	Texture = (texTexture);
    AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = Linear;
    MagFilter = Linear;    
};

const float tapWeight[4] = { 0.3f, 0.2f, 0.1f, 0.05f };
const float tapOffset[3] = { 0.003f, 0.006f, 0.009f };

float _scale = 1;

struct VS_INPUT {
    float4 position : POSITION;
    float2 texCoord : TEXCOORD0;
};
struct VS_OUTPUT {
	float4 position : POSITION;	
	float2 Tap0 : TEXCOORD0;
	float2 Tap1 : TEXCOORD1;
	float2 Tap2 : TEXCOORD2;
	float2 Tap3 : TEXCOORD3;
	float2 Tap1Neg : TEXCOORD4;
	float2 Tap2Neg : TEXCOORD5;
	float2 Tap3Neg : TEXCOORD6;
};
#define PS_INPUT VS_OUTPUT

VS_OUTPUT VS(VS_INPUT IN, uniform float2 DIRECTION) {
	VS_OUTPUT OUT;
	
	OUT.position = IN.position;
	
	OUT.Tap0 = IN.texCoord;
	
	OUT.Tap1 = IN.texCoord + tapOffset[0] * _scale * DIRECTION;
	OUT.Tap1Neg = IN.texCoord - tapOffset[0] * _scale * DIRECTION;
	OUT.Tap2 = IN.texCoord + tapOffset[1] * _scale * DIRECTION;
	OUT.Tap2Neg = IN.texCoord - tapOffset[1] * _scale * DIRECTION;
	OUT.Tap3 = IN.texCoord + tapOffset[2] * _scale * DIRECTION;
	OUT.Tap3Neg = IN.texCoord - tapOffset[2] * _scale * DIRECTION;
	
	return OUT;
}

float4 PS(PS_INPUT IN) : COLOR {
	float color;
	
	// Center Tap
	color = tex2D(sampTexture, IN.Tap0).r * tapWeight[0];
	
	// Inner Taps	
	color += tex2D(sampTexture, IN.Tap1).r * tapWeight[1];
	color += tex2D(sampTexture, IN.Tap2).r * tapWeight[2];
	color += tex2D(sampTexture, IN.Tap3).r * tapWeight[3];
	color += tex2D(sampTexture, IN.Tap1Neg).r * tapWeight[1];
	color += tex2D(sampTexture, IN.Tap2Neg).r * tapWeight[2];
	color += tex2D(sampTexture, IN.Tap3Neg).r * tapWeight[3];	
	
	return float4(color, color, color, 1);
}

technique TSM3 {
    pass HBlur {   
      VertexShader = compile vs_3_0 VS(float2(1, 0));
      PixelShader  = compile ps_3_0 PS();
    }
    pass VBlur {   
      VertexShader = compile vs_3_0 VS(float2(0, 1));
      PixelShader  = compile ps_3_0 PS();
    }    
}
technique TSM2 {
    pass HBlur {   
      VertexShader = compile vs_2_0 VS(float2(1, 0));
      PixelShader  = compile ps_2_0 PS();
    }
    pass VBlur {   
      VertexShader = compile vs_2_0 VS(float2(0, 1));
      PixelShader  = compile ps_2_0 PS();
    }    
}