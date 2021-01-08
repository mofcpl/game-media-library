#pragma warning(disable: 4005)
#include "DirectX_11-ErrorChecking.h"

struct QuadCoord
{
float LeftDownX,LeftDownY,LeftUpX,LeftUpY,RightDownX,RightDownY,RightUpX,RightUpY;
};

class cImage
{
private:

	ID3D11ShaderResourceView* Texture;
	float texWidth,texHeight;

public:
	
	friend class cSurface;

	void LoadTexture(ID3D11Device* device,LPCWSTR path);

	cImage();
	~cImage();

};
