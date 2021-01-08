#include"DirectX_11-ErrorChecking.h"

void CheckError(HRESULT error,LPCWSTR text)
{

	if(FAILED(error)) MessageBox(NULL, DXGetErrorDescription(error),text, MB_OK);	
			
}