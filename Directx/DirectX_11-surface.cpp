#include "DirectX_11-surface.h"


cSurface::cSurface()
{
	
	IsBufferSet = false;

	inuseTexture=0;
	QuadCount=0;

	MapType=D3D11_MAP_WRITE_DISCARD;

}

void cSurface::CreateSurface(IDXGISwapChain* swapchain, ID3D11Device* device, ID3D11DeviceContext* devcon, ID3D11DepthStencilView* depthview, ID3D11Buffer* objectbuffer, ID3D11RenderTargetView* rendertarget, int width, int height)
{


	Width=width;
	Height=height;
		
	pSwapChain = swapchain;
	pd3d11Device = device;
	pd3d11DevCon = devcon;
	pdepthStencilView = depthview;
	pcbPerObjectBuffer = objectbuffer;
	prenderTargetView = rendertarget;
	
	
	//BUFOR INDEKSOW
		
	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory( &indexBufferDesc, sizeof(indexBufferDesc) );

	indexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	//indexBufferDesc.ByteWidth = sizeof(DWORD)* 100;
	indexBufferDesc.ByteWidth = D3D11_REQ_MULTI_ELEMENT_STRUCTURE_SIZE_IN_BYTES;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	indexBufferDesc.MiscFlags = 0;

	hr = pd3d11Device->CreateBuffer(&indexBufferDesc, 0, &IndexBuffer);
	CheckError(hr,L"Create indexBuffer");

	
	//BUFOR WIERZCHOLKOW
	
	D3D11_BUFFER_DESC vertexBufferDesc;
	
	ZeroMemory( &vertexBufferDesc, sizeof(vertexBufferDesc) );

	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	//vertexBufferDesc.ByteWidth = sizeof( Vertex ) * 100;
	vertexBufferDesc.ByteWidth = D3D11_REQ_MULTI_ELEMENT_STRUCTURE_SIZE_IN_BYTES;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	
	hr = pd3d11Device->CreateBuffer( &vertexBufferDesc, 0, &VertBuffer); 
	CheckError(hr,L"Create vertexBuffer");


	//WLASCIWOSCI WYPELNIANIA 
	
	D3D11_RASTERIZER_DESC wfdesc;

	ZeroMemory(&wfdesc, sizeof(D3D11_RASTERIZER_DESC));
	wfdesc.AntialiasedLineEnable = false;
	wfdesc.CullMode = D3D11_CULL_BACK;
	wfdesc.DepthBias = 0;
	wfdesc.DepthBiasClamp = 0.0f;
	wfdesc.DepthClipEnable = true;
	wfdesc.FillMode = D3D11_FILL_SOLID;
	wfdesc.FrontCounterClockwise = false;
	wfdesc.MultisampleEnable = false;
	wfdesc.ScissorEnable = false;
	wfdesc.SlopeScaledDepthBias = 0.0f;
	
	hr = pd3d11Device->CreateRasterizerState(&wfdesc, &WireFrame);
	CheckError(hr,L"CreateRasterizerState");


	//WLASCIWOSCI NAKLADANIA TEKSTURY
	
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory( &sampDesc, sizeof(sampDesc) );
	sampDesc.Filter =  D3D11_FILTER_COMPARISON_ANISOTROPIC;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = 0;
	sampDesc.MaxAnisotropy=0;

	hr = pd3d11Device->CreateSamplerState( &sampDesc, &CubesTexSamplerState );
	CheckError(hr,L"CreateSamplerState");
	pd3d11DevCon->PSSetSamplers( 0, 1, &CubesTexSamplerState );
	
	//SPOSOBY MIESZANIA KOLOROW

	//Przezroczystosc
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory( &blendDesc, sizeof(blendDesc) );
	
	D3D11_RENDER_TARGET_BLEND_DESC rtbd;
	ZeroMemory( &rtbd, sizeof(rtbd) );

	//przezroczystosc
	
	rtbd.BlendEnable			 = true;
	rtbd.SrcBlend				 = D3D11_BLEND_BLEND_FACTOR;
	rtbd.DestBlend				 = D3D11_BLEND_INV_BLEND_FACTOR;
	rtbd.BlendOp				 = D3D11_BLEND_OP_ADD;
	rtbd.SrcBlendAlpha			 = D3D11_BLEND_ZERO;
	rtbd.DestBlendAlpha			 = D3D11_BLEND_ZERO;
	rtbd.BlendOpAlpha			 = D3D11_BLEND_OP_ADD;
	rtbd.RenderTargetWriteMask	 = 0x0F;

	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.IndependentBlendEnable = false;
	blendDesc.RenderTarget[0] = rtbd;
	
	hr = pd3d11Device->CreateBlendState(&blendDesc, &Transparency);
	CheckError(hr,L"CreateBlendState");
	
	//dodawanie kolorow
	
	rtbd.BlendEnable			 = true;
	rtbd.SrcBlend				 = D3D11_BLEND_BLEND_FACTOR;
	rtbd.DestBlend				 = D3D11_BLEND_ONE;
	rtbd.BlendOp				 = D3D11_BLEND_OP_ADD;
	rtbd.SrcBlendAlpha			 = D3D11_BLEND_ONE;
	rtbd.DestBlendAlpha			 = D3D11_BLEND_ZERO;
	rtbd.BlendOpAlpha			 = D3D11_BLEND_OP_ADD;
	rtbd.RenderTargetWriteMask	 = 0x0F;

	blendDesc.RenderTarget[0] = rtbd;
	
	hr = pd3d11Device->CreateBlendState(&blendDesc, &Add);
	CheckError(hr,L"CreateBlendState");
	
	//odejmowanie kolorow

	rtbd.BlendEnable			 = true;
	rtbd.SrcBlend				 = D3D11_BLEND_BLEND_FACTOR;
	rtbd.DestBlend				 = D3D11_BLEND_ONE;
	rtbd.BlendOp				 = D3D11_BLEND_OP_SUBTRACT;
	rtbd.SrcBlendAlpha			 = D3D11_BLEND_ONE;
	rtbd.DestBlendAlpha			 = D3D11_BLEND_ZERO;
	rtbd.BlendOpAlpha			 = D3D11_BLEND_OP_ADD;
	rtbd.RenderTargetWriteMask	 = 0x0F;

	blendDesc.RenderTarget[0] = rtbd;
	
	hr = pd3d11Device->CreateBlendState(&blendDesc, &Substract);
	CheckError(hr,L"CreateBlendState");

	//odwrocone odejmowanie
	
	rtbd.BlendEnable			 = true;
	rtbd.SrcBlend				 = D3D11_BLEND_BLEND_FACTOR;
	rtbd.DestBlend				 = D3D11_BLEND_ONE;
	rtbd.BlendOp				 = D3D11_BLEND_OP_REV_SUBTRACT;
	rtbd.SrcBlendAlpha			 = D3D11_BLEND_ONE;
	rtbd.DestBlendAlpha			 = D3D11_BLEND_ZERO;
	rtbd.BlendOpAlpha			 = D3D11_BLEND_OP_ADD;
	rtbd.RenderTargetWriteMask	 = 0x0F;

	blendDesc.RenderTarget[0] = rtbd;
	
	hr = pd3d11Device->CreateBlendState(&blendDesc, &RevSubstract);
	CheckError(hr,L"CreateBlendState");
	
	//Wieksza wartosc
	
	rtbd.BlendEnable			 = true;
	rtbd.SrcBlend				 = D3D11_BLEND_BLEND_FACTOR;
	rtbd.DestBlend				 = D3D11_BLEND_ONE;
	rtbd.BlendOp				 = D3D11_BLEND_OP_MAX;
	rtbd.SrcBlendAlpha			 = D3D11_BLEND_ONE;
	rtbd.DestBlendAlpha			 = D3D11_BLEND_ZERO;
	rtbd.BlendOpAlpha			 = D3D11_BLEND_OP_ADD;
	rtbd.RenderTargetWriteMask	 = 0x0F;

	blendDesc.RenderTarget[0] = rtbd;
	
	hr = pd3d11Device->CreateBlendState(&blendDesc, &Max);
	CheckError(hr,L"CreateBlendState");

	//Mniejsza wartosc

	rtbd.BlendEnable			 = true;
	rtbd.SrcBlend				 = D3D11_BLEND_BLEND_FACTOR;
	rtbd.DestBlend				 = D3D11_BLEND_ONE;
	rtbd.BlendOp				 = D3D11_BLEND_OP_MIN;
	rtbd.SrcBlendAlpha			 = D3D11_BLEND_ONE;
	rtbd.DestBlendAlpha			 = D3D11_BLEND_ZERO;
	rtbd.BlendOpAlpha			 = D3D11_BLEND_OP_ADD;
	rtbd.RenderTargetWriteMask	 = 0x0F;

	blendDesc.RenderTarget[0] = rtbd;
	
	hr = pd3d11Device->CreateBlendState(&blendDesc, &Min);
	CheckError(hr,L"CreateBlendState");
	
	//USTAW BUFORY 

	UINT stride = sizeof( Vertex );
	UINT offset = 0;
	pd3d11DevCon->IASetVertexBuffers( 0, 1, &VertBuffer, &stride, &offset );
	pd3d11DevCon->IASetIndexBuffer( IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	
	//DOMYSLNY TRYB MIESZANIA
	pd3d11DevCon->OMSetBlendState(0, 0, 0xffffffff);
	

}

void cSurface::SetCamera(cCamera* camera)
{
	//Set the Viewport
	pd3d11DevCon->RSSetViewports(1, &camera->viewport);

	//USTAWIENIA KAMERY

	camera->World = XMMatrixIdentity();
	camera->WVP = camera->World * camera->camView * camera->camProjection;
	cbPerObj.WVP = XMMatrixTranspose(camera->WVP);


}


void cSurface::SetBlending(float tr,mode blendtype)
{

	//MIESZANIE KOLOROW
	
	float blendFactor[] = {tr, tr, tr, 1.0f};
	
	
	
	if (blendtype==NONE)
	{
		if (tr>=1) 
		{	
			pd3d11DevCon->OMSetBlendState(0, 0, 0xffffffff);
		}
		else
		{
			
			pd3d11DevCon->OMSetBlendState(Transparency, blendFactor, 0xffffffff);
	
		}
	}

	if(blendtype==ADD)		pd3d11DevCon->OMSetBlendState(Add, blendFactor, 0xffffffff);
	if(blendtype==SUB)		pd3d11DevCon->OMSetBlendState(Substract, blendFactor, 0xffffffff);
	if(blendtype==REVSUB)	pd3d11DevCon->OMSetBlendState(RevSubstract, blendFactor, 0xffffffff);
	if(blendtype==MAX)		pd3d11DevCon->OMSetBlendState(Max, blendFactor, 0xffffffff);
	if(blendtype==MIN)		pd3d11DevCon->OMSetBlendState(Min, blendFactor, 0xffffffff);

}

void cSurface::SetPSEffect(cPixelShader* ps)
{
	pd3d11DevCon->PSSetShader(ps->ReturnPS(), 0, 0);
}

void cSurface::SetVSEffect(cVertexShader* vs)
{
	pd3d11DevCon->VSSetShader(vs->ReturnVS(), 0, 0);
	
	hr = pd3d11Device->CreateInputLayout(layout, numElements, vs->ReturnVSBuffer()->GetBufferPointer(), vs->ReturnVSBuffer()->GetBufferSize(), &VertLayout);
	CheckError(hr, L"CreateInputLayout");
	
	pd3d11DevCon->IASetInputLayout(VertLayout);
}

void cSurface::Draw(cImage* image,float posx,float posy,float posz,float scale,float rotation,QuadCoord* modify)
{

	if(inuseTexture!=0 && inuseTexture!=image->Texture)
	{
		Flush();
	}
	
	float LeftDownX, LeftDownY, LeftUpX, LeftUpY, RightDownX, RightDownY, RightUpX, RightUpY, texwidth, texheight;
	
	texwidth=image->texWidth;
	texheight=image->texHeight;
	
	if (scale!=0)
	{
		texwidth	*=scale;
		texheight	*=scale;
	}
		
	LeftDownX	= posx - texwidth/2;
	LeftDownY	= posy - texheight/2;
	LeftUpX		= posx - texwidth/2;
	LeftUpY		= posy + texheight/2;
	RightUpX	= posx + texwidth/2;
	RightUpY	= posy + texheight/2;
	RightDownX	= posx + texwidth/2;
	RightDownY	= posy - texheight/2;

	if (modify!=0)
	{
	
		LeftDownX	+= modify->LeftDownX*scale;
		LeftDownY	+= modify->LeftDownY*scale;
		LeftUpX		+= modify->LeftUpX*scale	;
		LeftUpY		+= modify->LeftUpY*scale;
		RightUpX	+= modify->RightUpX*scale;
		RightUpY	+= modify->RightUpY	*scale;
		RightDownX	+= modify->RightDownX*scale;
		RightDownY	+= modify->RightDownY*scale;

	}
	
	

	if(rotation!=0 && rotation!=360)
	{
		
		rotation = rotation/180*XM_PI;
	
		float rLeftDownX,rLeftDownY,rLeftUpX,rLeftUpY,rRightDownX,rRightDownY,rRightUpX,rRightUpY;

		
		rLeftDownX	= (LeftDownX-posx)*XMScalarCos(rotation)-(LeftDownY-posy)*XMScalarSin(rotation)+posx;
		rLeftDownY	= (LeftDownX-posx)*XMScalarSin(rotation)+(LeftDownY-posy)*XMScalarCos(rotation)+posy;
	
		rLeftUpX	= (LeftUpX-posx)*XMScalarCos(rotation)-(LeftUpY-posy)*XMScalarSin(rotation)+posx;
		rLeftUpY	= (LeftUpX-posx)*XMScalarSin(rotation)+(LeftUpY-posy)*XMScalarCos(rotation)+posy;
	
		rRightUpX	= (RightUpX-posx)*XMScalarCos(rotation)-(RightUpY-posy)*XMScalarSin(rotation)+posx;
		rRightUpY	= (RightUpX-posx)*XMScalarSin(rotation)+(RightUpY-posy)*XMScalarCos(rotation)+posy;
	
		rRightDownX	= (RightDownX-posx)*XMScalarCos(rotation)-(RightDownY-posy)*XMScalarSin(rotation)+posx;
		rRightDownY	= (RightDownX-posx)*XMScalarSin(rotation)+(RightDownY-posy)*XMScalarCos(rotation)+posy;
	
		LeftDownX	= rLeftDownX;
		LeftDownY	= rLeftDownY;
		LeftUpX		= rLeftUpX;
		LeftUpY		= rLeftUpY;
		RightUpX	= rRightUpX;
		RightUpY	= rRightUpY;
		RightDownX	= rRightDownX;
		RightDownY	= rRightDownY;
	
	}

	Vertex quad[4];

	quad[0] = Vertex(LeftDownX, LeftDownY,	posz, 0.0f, 1.0f); //lewy dolny rog
	quad[1] = Vertex(LeftUpX, LeftUpY, posz, 0.0f, 0.0f); //lewy gorny rog
	quad[2] = Vertex(RightUpX, RightUpY, posz, 1.0f, 0.0f); //prawy gorny rog
	quad[3] = Vertex(RightDownX, RightDownY, posz, 1.0f, 1.0f); //prawy dolny rog



	D3D11_MAPPED_SUBRESOURCE resource;
	ZeroMemory(&resource,sizeof(resource));

	hr = pd3d11DevCon->Map(VertBuffer, 0, MapType, 0, &resource);
	CheckError(hr,L"Map-VertBuffer");
	
	char* bufferData = static_cast<char*>(resource.pData);
	memcpy(bufferData+QuadCount*sizeof(quad), &quad, sizeof(quad));
    pd3d11DevCon->Unmap(VertBuffer, 0);

	DWORD QuadIndices[6];
	
	QuadIndices[0] = 0+4*QuadCount;
	QuadIndices[1] = 1+4*QuadCount;
	QuadIndices[2] = 2+4*QuadCount;
	QuadIndices[3] = 0+4*QuadCount;
	QuadIndices[4] = 2+4*QuadCount;
	QuadIndices[5] = 3+4*QuadCount;

	ZeroMemory(&resource,sizeof(resource));

	hr = pd3d11DevCon->Map(IndexBuffer, 0, MapType, 0, &resource);
	CheckError(hr,L"Map-IndexBuffer");

	bufferData = static_cast<char*>(resource.pData);
	memcpy(bufferData+QuadCount*sizeof(DWORD)*6,&QuadIndices,sizeof(DWORD)*6);
	pd3d11DevCon->Unmap(IndexBuffer,0);
	
	inuseTexture = image->Texture;
	QuadCount++;
	MapType=D3D11_MAP_WRITE_NO_OVERWRITE;

}




void cSurface::Flush()
{

	pd3d11DevCon->UpdateSubresource(pcbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0);
	pd3d11DevCon->VSSetConstantBuffers( 0, 1, &pcbPerObjectBuffer );
	pd3d11DevCon->PSSetShaderResources( 0, 1, &inuseTexture );
	pd3d11DevCon->RSSetState(WireFrame);
	pd3d11DevCon->DrawIndexed( 6*QuadCount, 0,0);

	

	MapType=D3D11_MAP_WRITE_DISCARD;
	QuadCount=0;
	inuseTexture=0;

	}

void cSurface::Clear(float red,float green, float blue)
{
D3DXCOLOR bgColor(red, green, blue, 0.0f);
pd3d11DevCon->ClearRenderTargetView(prenderTargetView, bgColor);


pd3d11DevCon->ClearDepthStencilView(pdepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
CheckError(hr,L"ClearDepth");

}

void cSurface::Present(bool vsync_enabled)
{
	// Present the back buffer to the screen since rendering is complete.
	if (vsync_enabled)
	{
		// Lock to screen refresh rate.
		pSwapChain->Present(1, 0);
	}
	else
	{
		// Present as fast as possible.
		pSwapChain->Present(0, 0);
	}

	return;
}

cSurface::~cSurface()
{
	Transparency->Release();
	Add->Release();
	Substract->Release();
	Max->Release();
	Min->Release();
	RevSubstract->Release();
	WireFrame->Release();
	CubesTexSamplerState->Release();
		
	IndexBuffer->Release();
	VertBuffer->Release();
	VertLayout->Release();

}