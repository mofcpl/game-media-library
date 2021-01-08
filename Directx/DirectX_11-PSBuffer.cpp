#include"DirectX_11-PSBuffer.h"



cPixelShader::cPixelShader(ID3D11Device* device)
{
	pd3d11Device = device;
}

void cPixelShader::LoadPS(LPCWSTR path)
{
	hr = D3DX11CompileFromFile(path, 0, 0, "PS", "ps_4_0", 0, 0, 0, &PS_Buffer, 0, 0);
	CheckError(hr,L"Pixel shader loading");

	hr = pd3d11Device->CreatePixelShader(PS_Buffer->GetBufferPointer(), PS_Buffer->GetBufferSize(), NULL, &PS);
	CheckError(hr,L"CreatePixelShader");
}

cPixelShader::~cPixelShader()
{
	
		PS->Release();
		PS_Buffer->Release();
	
}

ID3D11PixelShader* cPixelShader::ReturnPS()
{
return PS;
}