
cbuffer cbPerObject
{
	float4x4 WVP;
};

Texture2D ObjTexture;
SamplerState ObjSamplerState;

struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float2 TexCoord : TEXCOORD;
};

VS_OUTPUT VS(float4 inPos : POSITION, float2 inTexCoord : TEXCOORD)
{
    VS_OUTPUT output;

    output.Pos = mul(inPos, WVP);
    output.TexCoord = inTexCoord;

    return output;
}

float4 PS(VS_OUTPUT input) : SV_TARGET 
{
    float4 Color = ObjTexture.Sample( ObjSamplerState, input.TexCoord );

    clip(Color.a - .25);
    return Color; 
}

float4 BLUR(VS_OUTPUT input) : SV_TARGET 
{

  // TOP ROW
  float4 s11 = ObjTexture.Sample(ObjSamplerState,input.TexCoord + float2(-1.0f / 1024.0f, -1.0f / 768.0f));    // LEFT
  float4 s12 = ObjTexture.Sample(ObjSamplerState,input.TexCoord + float2(0, -1.0f / 768.0f));              // MIDDLE
  float4 s13 =ObjTexture.Sample(ObjSamplerState, input.TexCoord + float2(1.0f / 1024.0f, -1.0f / 768.0f)); // RIGHT
 
  // MIDDLE ROW
  float4 s21 =ObjTexture.Sample(ObjSamplerState, input.TexCoord + float2(-1.0f / 1024.0f, 0));             // LEFT
   float4 Color = ObjTexture.Sample( ObjSamplerState, input.TexCoord );                                         // DEAD CENTER
  float4 s23 = ObjTexture.Sample(ObjSamplerState,input.TexCoord + float2(-1.0f / 1024.0f, 0));                 // RIGHT
 
  // LAST ROW
  float4 s31 =ObjTexture.Sample(ObjSamplerState, input.TexCoord + float2(-1.0f / 1024.0f, 1.0f / 768.0f)); // LEFT
  float4 s32 = ObjTexture.Sample(ObjSamplerState,input.TexCoord + float2(0, 1.0f / 768.0f));                   // MIDDLE
  float4 s33 = ObjTexture.Sample(ObjSamplerState,input.TexCoord + float2(1.0f / 1024.0f, 1.0f / 768.0f));  // RIGHT
 
  // Average the color with surrounding samples
  Color = (Color + s11 + s12 + s13 + s21 + s23 + s31 + s32 + s33) / 9;

  
    clip(Color.a - .25);
    return Color; 
}