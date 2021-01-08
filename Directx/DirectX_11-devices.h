#pragma warning(disable: 4005)
#pragma once

#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")



#include <Windows.h>
#include <d3dx11.h>
#include <d3d11.h>
#include <d3dx10.h>

#include "DirectX_11-surface.h"
#include "DirectX_11-IA.h"
#include "DirectX_11-ErrorChecking.h"


class cDirectX
{
private:
	
	HRESULT hr;
	
	HWND Handle;
	HINSTANCE hInstance;
	__int16 Width;
	__int16 Height;
	
	ID3D11Buffer* cbPerObjectBuffer;
	
	IDXGISwapChain* SwapChain;
	ID3D11Device* d3d11Device;
	ID3D11DeviceContext* d3d11DevCon;
	ID3D11DepthStencilState* depthStencilState;
	ID3D11DepthStencilState* depthStencilStateNoDepth;
	ID3D11DepthStencilView* depthStencilView;
	ID3D11Texture2D* depthStencilBuffer;
	ID3D11RenderTargetView* renderTargetView;

	

public:
	
	ID3D11Device* GetDXdevice();
	ID3D11DeviceContext* GetDXdevcon();
	cbPerObject* GetDXcbPerObj();
	
	void SetSurface(cSurface* surface);
	void ReleaseObjects();

	void TurnDepthOn();
	void TurnDepthOff();

	cDirectX(int width, int height, HINSTANCE hinstance, HWND handle, UINT RefreshRate, D3D_DRIVER_TYPE DriverType);
	~cDirectX();

};