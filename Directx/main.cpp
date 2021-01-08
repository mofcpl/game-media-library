#pragma warning(disable: 4005)

#include<string>
#include<time.h>


#include"Framework.h"

#include"DirectX_11-devices.h"
#include "FW1FontWrapper-Text.h"
#include "RTLControl.h"
#include "DirectX_11-Input.h"
#include "DirectX_11-Audio.h"


IUnknown * pXAPO;
cWindow* framework;
cDirectX* Graph;
cSurface* Canvas;
cImage* background;
cImage* red;
cImage* green;
cImage* blue;
cImage* niedzwiedz;
cTimer* timer;
QuadCoord pochylenie;
cInput* wejscie;

cPixelShader* PS;
cVertexShader* VS;



float startTime, currentTime;

cCamera* Kamera;

cTextBox* tekst;

cFPS* licznik;
cFPS* licznik2;

cAudio* Dzwiek;
cSound* Shell;
cSound* Music;


FW1_RECTF box,box2;

int Count2=0;
float GameTime2;

float dt2;
std::wstring fps,fps2;

float camposX, camposY, camposZ,camtargetX,camtargetY,camtargetZ;

int x,y;
float scale;
float rotation;

float volumes[1];

PosXY mousepos;

XAUDIO2_FILTER_PARAMETERS param;

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance, LPSTR lpCmdLine,int nShowCmd)
{

	framework = new cWindow(hInstance,nShowCmd,1280,720,false,L"fhfgsdjdrtsrjt");
	Graph = new cDirectX(1280,720,hInstance,framework->WindowHandle(),60,D3D_DRIVER_TYPE_HARDWARE);
	Canvas = new cSurface();
	Graph->SetSurface(Canvas);

	PS = new cPixelShader(Graph->GetDXdevice());
	VS = new cVertexShader(Graph->GetDXdevice());
	PS->LoadPS(L"Effects.fx");
	VS->LoadVS(L"Effects.fx");

	Canvas->SetPSEffect(PS);
	Canvas->SetVSEffect(VS);

	Kamera = new cCamera(1280, 720);
	Canvas->SetCamera(Kamera);
	Kamera->ChangeToOrthographic();
	
	background = new cImage;
	background->LoadTexture(Graph->GetDXdevice(),L"background.jpg");

	red = new cImage;
	red->LoadTexture(Graph->GetDXdevice(),L"red.png");

	green= new cImage;
	green->LoadTexture(Graph->GetDXdevice(),L"green.png");

	blue= new cImage;
	blue->LoadTexture(Graph->GetDXdevice(),L"blue.png");

	niedzwiedz = new cImage;
	niedzwiedz->LoadTexture(Graph->GetDXdevice(),L"bullet.png");

	
	ZeroMemory(&pochylenie,sizeof(QuadCoord));
	pochylenie.LeftUpX=-200;
	pochylenie.RightUpX=-200;

	tekst=new cTextBox(Graph->GetDXdevice(),Graph->GetDXdevcon());

	box.Bottom=500;
	box.Top=10;
	box.Left=10;
	box.Right=300;

	box2.Bottom=500;
	box2.Top=100;
	box2.Left=10;
	box2.Right=300;


	tekst->ChangeColor(0xff999999);

	timer= new cTimer(0.017f,1.0);
	
	GameTime2=timer->GetTime();

	licznik = new cFPS(timer->GetTime());
	licznik2 = new cFPS(timer->GetTime());

	wejscie= new cInput(hInstance,framework->WindowHandle());
	
	x=100;
	y=100;
	scale=1;
	rotation=0;

	camposX = 640;
	camposY = 360;
	camposZ = -1.0f;
	camtargetZ = 1.0f;

	Dzwiek = new cAudio();
	Shell = new cSound();
	Music = new cSound();

	volumes[0] = 0;
	volumes[1] = 1.0f;
	
	Dzwiek->Load("shell.wav", Shell);
	Shell->SetChannelVolumes(2, volumes);
	Dzwiek->Start(Shell);

	volumes[1] = 1.0f;
	volumes[0] = 1.0f;

	param.Type= LowPassFilter;
	param.Frequency = XAUDIO2_MAX_FILTER_FREQUENCY;
	param.OneOverQ = XAUDIO2_MAX_FILTER_ONEOVERQ;

	
	Dzwiek->Load("music.wav", Music);
	Music->SetChannelVolumes(2, volumes);
	Music->SetFilter(param);
	Music->SetFrequencyRatio(1.0f);
	Music->Loop(true);
	
	Shell->EffectEcho(0.5f, 0.9f, 0.5f);


	Dzwiek->Start(Music);
	//Dzwiek->Submit(Music);
	//Graph->TurnDepthOn();
	framework->StartRealTimeLoop();

	Dzwiek->Stop(Music);
	Dzwiek->Stop(Shell);
	 
	delete timer;
	delete tekst;
	delete niedzwiedz;
	delete blue;
	delete green;
	delete red;
	delete background;
	delete Canvas;
	delete Graph;
	delete framework;
	return 0;

}

	
void cWindow::RealTimeLoop()
{
	
	timer->Calculate();		
	
	
	wejscie->UpdateState();
	mousepos.x += wejscie->GetMousePos().x;
	mousepos.y -= wejscie->GetMousePos().y;
	scale += wejscie->GetMousePos().rot*0.0005;
	
	if(timer->DoUpdate())
	{
	
		if (wejscie->KeyPressed(DIK_ESCAPE))PostMessage(hwnd, WM_DESTROY, 0, 0);
		if (wejscie->KeyPressed(DIK_LEFT)) x -= 1;
		if (wejscie->KeyPressed(DIK_RIGHT)) x += 1;
		if (wejscie->KeyPressed(DIK_UP)) y += 1;
		if (wejscie->KeyPressed(DIK_DOWN)) y -= 1;

		if (wejscie->KeyPressed(DIK_A)) camposX -= 5;
		if (wejscie->KeyPressed(DIK_D)) camposX += 5;
		if (wejscie->KeyPressed(DIK_W)) camposY += 5;
		if (wejscie->KeyPressed(DIK_S)) camposY -= 5;

		if (wejscie->MousePressed(0))
		{
			Dzwiek->Stop(Shell);
			Dzwiek->Flush(Shell);
			Dzwiek->Start(Shell);
			Dzwiek->Submit(Shell);
			
			
		}
	
		if (wejscie->MousePressed(0)) rotation += 5;

		

		licznik->Count(timer->GetTime());
		timer->Updated();
	}
		

		
	
	licznik2->Count(timer->GetTime());
	
	camtargetX = camposX;
	camtargetY = camposY;
	
	Kamera->SetCameraPosition(camposX, camposY, camposZ);
	Kamera->SetCameraTarget(camtargetX, camtargetY, camtargetZ);
	Kamera->ApplyChanges();
	Canvas->SetCamera(Kamera);
	
	fps=L"Logic FPS: ";
	fps+=std::to_wstring(licznik->ReturnFPS());

	fps2=L"Graphic FPS: ";
	fps2+=std::to_wstring(licznik2->ReturnFPS());
	
	const wchar_t* napis = fps.c_str();
	const wchar_t* napis2 = fps2.c_str();
	
	
	
	Canvas->SetBlending(1.0f,NONE);
	
	Canvas->Clear(0.0f, 0.0f, 0.0f);
	
	//Canvas->Draw(background, 640, 360, 0.0f, 1.0f, 0.0f, 0);

	Canvas->Draw(niedzwiedz, wejscie->GetMousePos().x, wejscie->GetMousePos().y, 5.0f, scale, rotation, NULL);
	
	Canvas->Draw(niedzwiedz, x, y, 15.0f, 1.0f, 0.0f, NULL);

	Canvas->Flush();

	
	
	
	tekst->Write(const_cast<wchar_t*>(napis),&box);
	tekst->Write(const_cast<wchar_t*>(napis2),&box2);
	Canvas->Flush();
	Canvas->Present(false);
	

	
		
}
