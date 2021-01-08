#include"FW1FontWrapper-Text.h"


cTextBox::cTextBox(ID3D11Device* device,ID3D11DeviceContext* devcon)
{
	
	pd3d11Device=device;
	pd3d11DevCon=devcon;
	Size=32;

	Font=L"Arial";
	Color=0xff000000;

	FW1CreateFactory(FW1_VERSION, &pFW1Factory);
	pFW1Factory->CreateFontWrapper(pd3d11Device, Font, &pFontWrapper);
}

cTextBox::~cTextBox()
{
	pFontWrapper->Release();
	pFW1Factory->Release();
}

void cTextBox::Write(WCHAR* string,FW1_RECTF *pLayoutRect)
{
		pFontWrapper->DrawString(
		pd3d11DevCon,
		string,
		Font,// String
		Size,// Font size
		pLayoutRect,
		Color,// Text color, 0xAaBbGgRr
		NULL,
		NULL,
		FW1_RESTORESTATE|FW1_ALIASED);
}

void cTextBox::ChangeFont(WCHAR* font)
{
Font=font;
}

void cTextBox::ChangeColor(UINT32 color)
{
Color=color;
}

void cTextBox::ChangeSize(float size)
{
	Size=size;
}