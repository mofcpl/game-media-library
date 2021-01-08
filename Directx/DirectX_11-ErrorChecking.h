#pragma once
#pragma comment (lib, "DXErr.lib")
#pragma warning(disable: 4005)

#include <d3dx11.h>
#include <DxErr.h>



void CheckError(HRESULT error,LPCWSTR text);


