#pragma once
#pragma warning(disable: 4005)
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>

#include"DirectX_11-ErrorChecking.h"



class cVertexShader
{
private:
	
	HRESULT hr;
	
	ID3D10Blob* VS_Buffer;
	ID3D11VertexShader* VS;

	ID3D11Device* pd3d11Device;
	
	
public:
	
	ID3D10Blob* ReturnVSBuffer();
	ID3D11VertexShader* ReturnVS();
	void LoadVS(LPCWSTR path);
	
	cVertexShader(ID3D11Device* device);

	~cVertexShader();


};
