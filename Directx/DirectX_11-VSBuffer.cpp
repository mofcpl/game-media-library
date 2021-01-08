#include "DirectX_11-VSBuffer.h"


cVertexShader::cVertexShader(ID3D11Device* device)
{
	
	pd3d11Device = device;
	
}

void cVertexShader::LoadVS(LPCWSTR path)
{
	hr = D3DX11CompileFromFile(path, 0, 0, "VS", "vs_4_0", 0, 0, 0, &VS_Buffer, 0, 0);
	CheckError(hr, path);

	hr = pd3d11Device->CreateVertexShader(VS_Buffer->GetBufferPointer(), VS_Buffer->GetBufferSize(), NULL, &VS);
	CheckError(hr, L"CreateVertexShader");
}


ID3D10Blob* cVertexShader::ReturnVSBuffer()
{
	return VS_Buffer;
}

ID3D11VertexShader* cVertexShader::ReturnVS()
{
	return VS;
}

cVertexShader::~cVertexShader()
{
	VS->Release();
	VS_Buffer->Release();
}

