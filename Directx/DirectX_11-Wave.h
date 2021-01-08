#include<XAudio2.h>
#include<XAudio2fx.h>
#include<XAPOFX.h>
#include"Load-wave.h"
#include"DirectX_11-ErrorChecking.h"



class cSound
{
private:

	IXAudio2SourceVoice* pSourceVoice;
	Wave* buffer;
	IUnknown * pXAPO;

	HRESULT hr;
public:

	friend class cAudio;

	void SetVolume(float volume);
	void SetChannelVolumes(int channel,float volumes[]);
	void SetFilter(XAUDIO2_FILTER_PARAMETERS parameters);
	void SetFrequencyRatio(float ratio);
	void Loop(bool looped);
	
	void EffectReverb(float diffusion, float roomsize);
	void EffectMasteringLimiter(UINT32 loudness, UINT32 release);
	void EffectEqualizer(FXEQ_PARAMETERS EqualizerParameters);
	void EffectEcho(float delay,float feedback, float wetdrymix);


	cSound();
	~cSound();

};
