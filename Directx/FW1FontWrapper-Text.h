#pragma warning(disable: 4005)
#include<FW1FontWrapper.h>
#pragma comment (lib, "FW1FontWrapper.lib")


class cTextBox
{
private:

	ID3D11Device* pd3d11Device;
	ID3D11DeviceContext* pd3d11DevCon;
	IFW1Factory *pFW1Factory;
	IFW1FontWrapper *pFontWrapper;

	WCHAR* Font;
	UINT32 Color;
	float Size;

public:

	void Write(WCHAR* string,FW1_RECTF *pLayoutRect);
	void ChangeFont(WCHAR* font);
	void ChangeColor(UINT32 color);
	void ChangeSize(float size);
	cTextBox(ID3D11Device* device,ID3D11DeviceContext* devcon);
	~cTextBox();

};