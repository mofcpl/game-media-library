#include "RTLControl.h"

cTimer::cTimer(float timestep,float maxaccumulated)
{
	dt = 0.0f;
	lastUpdateTime = GetTime();
	accumulator = 0.0f;

	TIME_STEP=timestep;
	MAX_ACCUMULATED_TIME=maxaccumulated;
	
	bUseQPC = (QueryPerformanceFrequency (&uFreq) != 0);
}

float cTimer::GetTime()
{
      LARGE_INTEGER uTicks;
      QueryPerformanceCounter (&uTicks);
      return (float)(uTicks.QuadPart / (double)uFreq.QuadPart);
}

void cTimer::Calculate()
{

	dt = GetTime() - lastUpdateTime; //obliczenie czasu od ostatniej klatki 
	lastUpdateTime += dt; //podmiana 
	dt = max(0, dt); 

	accumulator += dt; 
	accumulator = Clamp(accumulator, 0, MAX_ACCUMULATED_TIME);
}

bool cTimer::DoUpdate()
{
	if(accumulator > TIME_STEP)
	{
		return true;
	}
	else
	{
		return false;
	}
}

float cTimer::Clamp(float what,float a,float b)
{
	return min(b, max(what, a)); 

}

void cTimer::Updated()
{
	accumulator -= TIME_STEP;
}

cTimer::~cTimer()
{
}

////////////////////////////////////////////////////////////////

cFPS::cFPS(float time)
{
	Counter=0;
	Time=time;
	Delta=0;
	FPS=0;

}

void cFPS::Count(float time)
{
		Counter++;
		Delta=time-Time;
		if(Delta >= 1.0)
		{
			FPS=Counter;
			Counter=0;
			Time=time;
		}

}

int cFPS::ReturnFPS()
{
return FPS;
}

cFPS::~cFPS()
{
}