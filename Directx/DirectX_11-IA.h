#pragma once

#pragma warning(disable: 4005)
#include <d3dx11.h>
#include <d3d11.h>
#include <d3dx10.h>


#include <windows.h>
#include <xnamath.h>

struct Vertex	//Overloaded Vertex Structure
{
	Vertex(){}
	Vertex(float x, float y, float z,
		float u, float v)
		: pos(x,y,z), texCoord(u, v){}

	XMFLOAT3 pos;
	XMFLOAT2 texCoord;
};

extern D3D11_INPUT_ELEMENT_DESC layout[];

extern UINT numElements;

struct cbPerObject
{
	XMMATRIX  WVP;
};

