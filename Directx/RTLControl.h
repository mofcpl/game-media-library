#include<Windows.h>
#include<algorithm>

using std::min;
using std::max;

class cTimer
{
private:

	float dt;											//czas od ostatniej aktualizacji 
	float lastUpdateTime;								//czas ostatniej aktualizacji 
														//przykladowa funkcja GetCurrentTime() pobiera 
														//nam od systemu aktualny czas w sekundach 
	float accumulator;  
	float TIME_STEP;									//krok czasowy, a zarazem czas trwania ramki 
	float MAX_ACCUMULATED_TIME;							//fizyki w sekundach; tutaj 30 milisekund, czyli 
														//ok. 30 aktualizacji na sekunde 
														//maksymalny czas zgromadzony w pojedynczym														//obiegu petli glownej 
	LARGE_INTEGER uFreq;
	bool bUseQPC;

public:

	float GetTime();
	void Calculate();
	float Clamp(float what,float a,float b);
	bool DoUpdate();
	void Updated();
	
	cTimer(float timestep,float maxaccumulated);
	~cTimer();
};


class cFPS
{
private:
	int Counter;
	float Time;
	float Delta;
	int FPS;

public:

	void Count(float time);
	int ReturnFPS();

	cFPS(float time);
	~cFPS();

};