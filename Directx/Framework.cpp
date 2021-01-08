#include"Framework.h"


LRESULT CALLBACK cWindow::WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch( msg )
	{

		return 0;

		case WM_DESTROY: PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd,msg,wParam,lParam);
}

bool cWindow::InitializeWindow(HINSTANCE hInstance,int ShowWnd,int width, int height,bool windowed)
{
	typedef struct _WNDCLASS 
	{
	UINT cbSize;
	UINT style;
	WNDPROC lpfnWndProc;
	int cbClsExtra;
	int cbWndExtra;
	HANDLE hInstance;
	HICON hIcon;
	HCURSOR hCursor;
	HBRUSH hbrBackground;
	LPCTSTR lpszMenuName;
	LPCTSTR lpszClassName;

	} WNDCLASS;

	WNDCLASSEX wc;
	ZeroMemory(&wc,sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+2);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WndClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wc);

	hwnd = CreateWindowEx(NULL,WndClassName,L"Framework",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT, CW_USEDEFAULT,width, height,NULL,NULL,hInstance,NULL);

	ShowWindow(hwnd, ShowWnd);
	UpdateWindow(hwnd);
	
	return true;
}


WPARAM cWindow::StartRealTimeLoop()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while(true)
	{
		
		

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			break;
			TranslateMessage(&msg);	
			DispatchMessage(&msg);
		}

		else
		{
			RealTimeLoop();
		}
	}
	return msg.wParam;
}

cWindow::cWindow()
{
}

cWindow::~cWindow()
{
}