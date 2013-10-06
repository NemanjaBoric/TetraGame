//***************************************************************************************
// color.fx by Frank Luna (C) 2011 All Rights Reserved.
//
// Transforms and colors geometry.
//***************************************************************************************

cbuffer cbPerObject
{
	float4x4 gWorldViewProj; 
};

struct VertexIn
{
	float3 position  : POSITION;
    float4 Color : COLOR;
    float3 instancePosition : TEXCOORD1;
    float3 rotateAmount: TEXCOORD2;

};

struct VertexOut
{
	float4 PosH  : SV_POSITION;
    float4 Color : COLOR;
};

float4x4 RotationMatrix(float rotation)  
{  
    float c = cos(rotation);  
    float s = sin(rotation);  
 
    return float4x4(
        c,    -s,   0.0f, 0.0f,
        s,    c,    0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f, 
        0.0f, 0.0f, 0.0f, 1.0f   
    );  
} 

float4x4 IdentityMatrix4()
{
    return float4x4(
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1);
}

float4x4 NulMatrix()
{
    return float4x4(
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1);
}

float4x4 TranslationMatrix()
{
    return float4x4(
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0);
}


VertexOut VS(VertexIn input)
{
	VertexOut vout;

   float4x4 translateMatrix = input.rotateAmount.x != 0 ? TranslationMatrix() : NulMatrix();
   float4x4 tmp =  input.rotateAmount.x != 0 ? RotationMatrix(input.rotateAmount.x) :  IdentityMatrix4();
  
   vout.PosH = mul(tmp, float4(input.position, 1.0f));


   
    vout.PosH.x += input.instancePosition.x;
    vout.PosH.y += input.instancePosition.y;
    vout.PosH.z += input.instancePosition.z;
    

   vout.PosH = mul(vout.PosH, gWorldViewProj);
   
	// Just pass vertex color into the pixel shader.
    vout.Color = input.Color;
    
    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
    return pin.Color;
}

technique11 ColorTech
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS() ) );
    }
}
