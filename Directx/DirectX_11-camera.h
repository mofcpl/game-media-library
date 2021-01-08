#pragma once
#pragma warning(disable: 4005)
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <xnamath.h>

#include "DirectX_11-IA.h"



class cCamera
{
private:

	XMMATRIX WVP;
	XMMATRIX vpMatrix_;

	XMMATRIX World;
	XMMATRIX camView;
	XMMATRIX camProjection;
	
	XMVECTOR camPosition;
	XMVECTOR camTarget;
	XMVECTOR camUp;

	D3D11_VIEWPORT viewport;

	float FOV;
	float Width, Height;
	float FarZ, NearZ;

public:
	
	friend class cSurface;

	cCamera(FLOAT width, FLOAT height);

	void SetCameraPosition(float posx, float posy, float posz);
	void SetCameraTarget(float posx, float posy, float posz);
	void SetCameraUp(float posx, float posy, float posz);

	void SetSeeingInterval(float nearz, float farz);
	void SetFov(float fov);

	void ChangeToOrthographic();
	void ChangeToPerspective();

	void ApplyChanges();




};