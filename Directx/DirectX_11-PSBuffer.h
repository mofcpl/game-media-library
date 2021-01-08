#pragma once
#pragma warning(disable: 4005)
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>

#include"DirectX_11-ErrorChecking.h"



class cPixelShader
{
private:
	
	HRESULT hr;
	
	ID3D10Blob* PS_Buffer;
	ID3D11PixelShader* PS;

	ID3D11Device* pd3d11Device;


public:
	
	ID3D11PixelShader* ReturnPS();
	void LoadPS(LPCWSTR path);
	
	cPixelShader(ID3D11Device* device);
	~cPixelShader();


};