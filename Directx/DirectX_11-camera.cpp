#include"DirectX_11-camera.h"



cCamera::cCamera(FLOAT width, FLOAT height)
{
	
	Width = width;
	Height = height;

	FOV = 0.4f;

	NearZ = 1.0f;
	FarZ = 1000.0f;

	//USTAWIENIA PROJEKCJI ORTAGONALNEJ

	camPosition = XMVectorSet(0.0f,0.0f, -1500.0f, 0.0f);
	camTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	camUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	//Set the View matrix
	camView = XMMatrixLookAtLH(camPosition, camTarget, camUp);
	
	camProjection = XMMatrixPerspectiveFovLH(FOV*3.14f, (float)width / height, 1.0f, 2000.0f);
	//camProjection = XMMatrixOrthographicOffCenterLH(0, width, 0, height, 1.0f, 100.0f);
	vpMatrix_ = XMMatrixMultiply(camView, camProjection);

	//WLASCIWOSCI WIDOKU

	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = width;
	viewport.Height = height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

}


void cCamera::SetCameraPosition(float posx, float posy, float posz)
{
	camPosition = XMVectorSet(posx, posy, posz, 0.0f);
}

void cCamera::SetCameraTarget(float posx, float posy, float posz)
{
	camTarget = XMVectorSet(posx, posy, posz, 0.0f);
}

void cCamera::SetCameraUp(float posx, float posy, float posz)
{
	camUp = XMVectorSet(posx, posy, posz, 0.0f);
}

void cCamera::SetFov(float fov)
{
	FOV = fov;
}

void cCamera::SetSeeingInterval(float nearz, float farz)
{
	NearZ = nearz;
	FarZ = farz;
}

void cCamera::ChangeToOrthographic()
{
	camProjection = XMMatrixOrthographicOffCenterLH(-Width/2, Width/2, -Height/2, Height/2, NearZ, FarZ);
}

void cCamera::ChangeToPerspective()
{
	camProjection = XMMatrixPerspectiveFovLH(FOV*3.14f, (float)Width / Height, NearZ, FarZ);
}

void cCamera::ApplyChanges()
{
	camView = XMMatrixLookAtLH(camPosition, camTarget, camUp);
	vpMatrix_ = XMMatrixMultiply(camView, camProjection);
}



