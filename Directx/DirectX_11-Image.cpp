#include"DirectX_11-Image.h"

void cImage::LoadTexture(ID3D11Device* device,LPCWSTR path)
{
	
	HRESULT hr;
	hr = D3DX11CreateShaderResourceViewFromFile( device, path,NULL, NULL, &Texture, NULL );
	CheckError(hr,L"CreateShaderResourceViewFromFile");
	

	
	ID3D11Resource* texResource;
	Texture->GetResource(&texResource);
	
	ID3D11Texture2D* tex;
	texResource->QueryInterface(&tex);
	
	D3D11_TEXTURE2D_DESC texdesc;
	tex->GetDesc(&texdesc);
	
	texWidth  = static_cast<float>(texdesc.Width);
	texHeight = static_cast<float>(texdesc.Height);

	if(static_cast<int>(texWidth)%2!=0 || static_cast<int>(texHeight)%2!=0) MessageBox(NULL,L"Loading texture",L"texture dimensions must be divisible by 2",MB_OK);
		
	tex->Release();
	texResource->Release();

}

cImage::cImage()
{
}

cImage::~cImage()
{
	Texture->Release();
}