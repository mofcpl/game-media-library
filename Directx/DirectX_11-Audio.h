#include<XAudio2.h>
#include"DirectX_11-Wave.h"
#include"DirectX_11-ErrorChecking.h"


class cAudio
{
private:
	
	IXAudio2* pXAudio2;
	IXAudio2MasteringVoice* pMasterVoice;


	HRESULT hr;

public:

	void Load(const char* path, cSound* wave);
	void Start(cSound* wave);
	void Stop(cSound* wave);
	void Submit(cSound* wave);
	void Flush(cSound* wave);

	cAudio();
	~cAudio();

};