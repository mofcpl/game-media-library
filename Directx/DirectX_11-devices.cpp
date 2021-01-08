#include "DirectX_11-devices.h"



ID3D11DeviceContext* cDirectX::GetDXdevcon()
{

return d3d11DevCon;
}

ID3D11Device* cDirectX::GetDXdevice()
{

return d3d11Device;
}

void cDirectX::SetSurface(cSurface* surface)
{

	surface->CreateSurface(SwapChain, d3d11Device, d3d11DevCon, depthStencilView, cbPerObjectBuffer, renderTargetView, Width, Height);

}

cDirectX::cDirectX(int width, int height, HINSTANCE hinstance, HWND handle, UINT RefreshRate, D3D_DRIVER_TYPE DriverType)
{
	
	hInstance=hinstance;
	Handle=handle;
	Width=width;
	Height=height;


	//Describe our Buffer
	DXGI_MODE_DESC bufferDesc;

	ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));

	bufferDesc.Width = Width;
	bufferDesc.Height = Height;
	bufferDesc.RefreshRate.Numerator = RefreshRate;
	bufferDesc.RefreshRate.Denominator = 1;
	bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	//Describe our SwapChain
	DXGI_SWAP_CHAIN_DESC swapChainDesc;

	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainDesc.BufferDesc = bufferDesc;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.OutputWindow = Handle;
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	//Create our SwapChain
	hr = D3D11CreateDeviceAndSwapChain(NULL, DriverType, NULL, NULL, NULL, NULL, D3D11_SDK_VERSION, &swapChainDesc, &SwapChain, &d3d11Device, NULL, &d3d11DevCon);
	CheckError(hr, L"CreateDeviceAndSwapChain");

	// Initialize the description of the depth buffer.

	D3D11_TEXTURE2D_DESC depthBufferDesc;
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

	// Set up the description of the depth buffer.

	depthBufferDesc.Width = Width;
	depthBufferDesc.Height = Height;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;


	// Create the texture for the depth buffer using the filled out description.
	d3d11Device->CreateTexture2D(&depthBufferDesc, NULL, &depthStencilBuffer);


	//Describe our Depth/Stencil Buffer
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;

	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	hr = d3d11Device->CreateDepthStencilState(&depthStencilDesc, &depthStencilState);
	CheckError(hr, L"CreateDepthStencilState");

	depthStencilDesc.DepthEnable = false;

	hr = d3d11Device->CreateDepthStencilState(&depthStencilDesc, &depthStencilStateNoDepth);
	CheckError(hr, L"CreateDepthStencilState");


	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
	depthStencilViewDesc.Format = DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;


	hr = d3d11Device->CreateDepthStencilView(depthStencilBuffer, &depthStencilViewDesc, &depthStencilView);
	CheckError(hr, L"CreateDepthStencilView");

	d3d11DevCon->OMSetDepthStencilState(depthStencilState, 1);

	D3D11_BUFFER_DESC cbbd;
	ZeroMemory(&cbbd, sizeof(D3D11_BUFFER_DESC));

	cbbd.Usage = D3D11_USAGE_DEFAULT;
	cbbd.ByteWidth = sizeof(cbPerObject);
	cbbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbbd.CPUAccessFlags = 0;
	cbbd.MiscFlags = 0;

	hr = d3d11Device->CreateBuffer(&cbbd, NULL, &cbPerObjectBuffer);
	CheckError(hr, L"Create cbPerObjectBuffer");

	//Create our BackBuffer
	ID3D11Texture2D* BackBuffer;
	hr = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);
	CheckError(hr, L"GetBuffer(BackBuffer))");

	//Create our Render Target
	hr = d3d11Device->CreateRenderTargetView(BackBuffer, NULL, &renderTargetView);
	CheckError(hr, L"CreateRenderTargetView");

	d3d11DevCon->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

	//USTAW TYP PRYMITYWOW

	d3d11DevCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}



cDirectX::~cDirectX()
{
	
	depthStencilView->Release();
	depthStencilBuffer->Release();
	depthStencilState->Release();
	SwapChain->Release();
	d3d11Device->Release();
	d3d11DevCon->Release();
	renderTargetView->Release();

}


void cDirectX::TurnDepthOff()
{
	d3d11DevCon->OMSetDepthStencilState(depthStencilStateNoDepth, 1);
}

void cDirectX::TurnDepthOn()
{
	d3d11DevCon->OMSetDepthStencilState(depthStencilState, 1);
}