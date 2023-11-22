#include"Particle.hlsli"

struct Material
{
    float32_t4 color; //���̐F
    int32_t enableLighting; //���C�g�̃t���O
    float32_t4x4 uvTransform; //uv��SRT
};

ConstantBuffer<Material> gMaterial : register(b0);
Texture2D<float32_t4> gTexture : register(t0);
SamplerState gSampler : register(s0);
struct PixelShaderOutput
{
    float32_t4 color : SV_TARGET0;
};

 
PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    float4 transformedUV = mul(float32_t4(input.texcoord, 0.0f, 1.0f), gMaterial.uvTransform);
    float32_t4 textureColor = gTexture.Sample(gSampler, transformedUV.xy);
    
    if (textureColor.a == 0.0)
    {
        discard;
    }
    if (textureColor.a <= 0.5)
    {
        discard;
    }
	
    output.color = gMaterial.color * textureColor;
	
    return output;
}