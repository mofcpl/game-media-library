#include"DirectX_11-Input.h"

cInput::cInput(HINSTANCE instance,HWND hwnd)
{

	hr = DirectInput8Create(instance,DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&DirectInput,NULL); 
	CheckError(hr,L"DirectInput8Create");

	hr = DirectInput->CreateDevice(GUID_SysKeyboard,&DIKeyboard,NULL);
	CheckError(hr,L"CreateDevice-DIKeyboard");

	hr = DirectInput->CreateDevice(GUID_SysMouse,&DIMouse,NULL);
	CheckError(hr,L"CreateDevice-DIMouse");

	hr = DIKeyboard->SetDataFormat(&c_dfDIKeyboard);
	hr = DIKeyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	hr = DIMouse->SetDataFormat(&c_dfDIMouse);
	hr = DIMouse->SetCooperativeLevel(hwnd, DISCL_EXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND);

}

void cInput::UpdateState()
{
	
	DIKeyboard->Acquire();
	DIMouse->Acquire();

	DIMouse->GetDeviceState(sizeof(DIMOUSESTATE), &mouseState);
	DIKeyboard->GetDeviceState(sizeof(keyboardState),(LPVOID)&keyboardState);

}

bool cInput::KeyPressed(int key)
{
	if(keyboardState[key] & 0x80) return true;

	return false;
}

PosXY cInput::GetMousePos()
{
	PosXY mousexy;

	mousexy.x = mouseState.lX;
	mousexy.y = mouseState.lY;
	mousexy.rot =  mouseState.lZ;

	return mousexy;

}

bool cInput::MousePressed(int key)
{
	if(mouseState.rgbButtons[key] & 0x80) return true;

	return false;
}

cInput::~cInput()
{
	DIKeyboard->Unacquire();
	DIMouse->Unacquire();
	DirectInput->Release();
}