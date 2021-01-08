#pragma once
#pragma warning(disable: 4005)
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <xnamath.h>

#include "DirectX_11-IA.h"
#include "DirectX_11-PSBuffer.h"
#include "DirectX_11-VSBuffer.h"
#include "DirectX_11-ErrorChecking.h"
#include "DirectX_11-Image.h"
#include "DirectX_11-camera.h"

enum  mode{NONE,ADD,SUB,REVSUB,MAX,MIN};

class cSurface
{

private:

	HRESULT hr;

	__int16 Width;
	__int16 Height;

	__int32 QuadCount;
	bool IsBufferSet;

	IDXGISwapChain* pSwapChain;
	ID3D11Device* pd3d11Device;
	ID3D11DeviceContext* pd3d11DevCon;
	ID3D11DepthStencilView* pdepthStencilView;
	ID3D11Buffer* pcbPerObjectBuffer;
	ID3D11RenderTargetView* prenderTargetView;
	
	
	cbPerObject cbPerObj;
	D3D11_MAP MapType;
	ID3D11ShaderResourceView* inuseTexture;
	
	ID3D11BlendState* Transparency;
	ID3D11BlendState* Add;
	ID3D11BlendState* Substract;
	ID3D11BlendState* Max;
	ID3D11BlendState* Min;
	ID3D11BlendState* RevSubstract;
	
	ID3D11RasterizerState* WireFrame;
	ID3D11SamplerState* CubesTexSamplerState;
			
	ID3D11Buffer* IndexBuffer;
	ID3D11Buffer* VertBuffer;
	
	ID3D11InputLayout* VertLayout;

	void CreateSurface(IDXGISwapChain* swapchain, ID3D11Device* device, ID3D11DeviceContext* devcon, ID3D11DepthStencilView* depthview, ID3D11Buffer* objectbuffer, ID3D11RenderTargetView* rendertarget, int width, int height);

public:

	friend class cDirectX;

	void Draw(cImage* image, float posx, float posy, float posz, float scale, float rotation, QuadCoord* modify);
	void Flush();
	void Clear(float red,float green, float blue);
	void Present(bool vsync_enabled);

	void SetCamera(cCamera* camera);
	void SetPSEffect(cPixelShader* ps);
	void SetVSEffect(cVertexShader* vs);
	void SetBlending(float tr,mode blendtype);
	
	cSurface();
	~cSurface();

};

