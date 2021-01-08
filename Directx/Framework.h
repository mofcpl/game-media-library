//
//		Framework by MofC
//
//		How to use:
//      -Define function RealTimeLoop() and put code in it
//		-Define function WinMain
//		-In Function WinMain use function StarRealTimeLoop();
//
//

#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>





class cWindow
{

private:

	LPCTSTR WndClassName;
	HWND hwnd;
	MSG msg;
	
	static LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);
	bool InitializeWindow(HINSTANCE hInstance,int ShowWnd,int width, int height,bool windowed);

public:

	HWND WindowHandle()
	{
	return hwnd;
	}
	
	cWindow(HINSTANCE hInstance,int ShowWnd,int width, int height,bool windowed,LPCTSTR ClassName) 
	{
		WndClassName=ClassName;
		
		if(!InitializeWindow(hInstance,ShowWnd,width,height,windowed))
		{
			MessageBox(0, L"Window Initialization - Failed",L"Error", MB_OK);
		}
	}
		
	void RealTimeLoop();
	WPARAM StartRealTimeLoop();

	cWindow();
	~cWindow();

};

