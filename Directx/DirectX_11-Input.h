#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>
#include"DirectX_11-ErrorChecking.h"

struct PosXY
{
int x;
int y;
int rot;
};

class cInput
{
private:

	IDirectInputDevice8* DIKeyboard;
	IDirectInputDevice8* DIMouse;

	LPDIRECTINPUT8 DirectInput;

	DIMOUSESTATE mouseState;
	BYTE keyboardState[256];

	HRESULT hr;

public:

	void UpdateState();

	bool KeyPressed(int key);
	bool MousePressed(int key);
	PosXY GetMousePos();
	
	cInput(HINSTANCE instance,HWND hwnd);
	~cInput();

};