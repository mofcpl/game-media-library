#include "DirectX_11-Wave.h"

cSound::cSound()
{
	buffer = new Wave;
}

void cSound::SetVolume(float volume)
{
	pSourceVoice->SetVolume(volume,NULL);
}

void cSound::SetChannelVolumes(int channelCount, float volumes[])
{
	pSourceVoice->SetChannelVolumes(channelCount,volumes);
}

void cSound::Loop(bool looped)
{
	if (looped == true)
	{
		buffer->m_xa.LoopCount = XAUDIO2_LOOP_INFINITE;
	}
	else
	{
		buffer->m_xa.LoopCount = 0;
	}

}
void cSound::SetFilter(XAUDIO2_FILTER_PARAMETERS parameters)
{
	pSourceVoice->SetFilterParameters(&parameters);
}

void cSound::SetFrequencyRatio(float ratio)
{
	pSourceVoice->SetFrequencyRatio(ratio);
}

void cSound::EffectReverb(float diffusion, float roomsize)
{
	IUnknown * pXAPO;
	CreateFX(__uuidof(FXReverb), &pXAPO);

	XAUDIO2_EFFECT_DESCRIPTOR descriptor;
	descriptor.InitialState = true;
	descriptor.OutputChannels = 2;
	descriptor.pEffect = pXAPO;


	XAUDIO2_EFFECT_CHAIN chain;
	chain.EffectCount = 1;
	chain.pEffectDescriptors = &descriptor;


	pSourceVoice->SetEffectChain(&chain);

	pXAPO->Release();

	FXREVERB_PARAMETERS XAPOParameters;
	XAPOParameters.Diffusion = diffusion; //Max 1.0f Min 0.0f default 0.9f
	XAPOParameters.RoomSize = roomsize;   //Max 1.0f Min 0.0001f deafult 0.6f

	pSourceVoice->SetEffectParameters(0, &XAPOParameters, sizeof(FXREVERB_PARAMETERS));

}

void cSound::EffectMasteringLimiter(UINT32 loudness, UINT32 release)
{
	IUnknown * pXAPO;
	CreateFX(__uuidof(FXMasteringLimiter), &pXAPO);

	XAUDIO2_EFFECT_DESCRIPTOR descriptor;
	descriptor.InitialState = true;
	descriptor.OutputChannels = 2;
	descriptor.pEffect = pXAPO;


	XAUDIO2_EFFECT_CHAIN chain;
	chain.EffectCount = 1;
	chain.pEffectDescriptors = &descriptor;


	pSourceVoice->SetEffectChain(&chain);

	pXAPO->Release();

	FXMASTERINGLIMITER_PARAMETERS XAPOParameters;
	XAPOParameters.Loudness = loudness;
	XAPOParameters.Release = release;


	pSourceVoice->SetEffectParameters(0, &XAPOParameters, sizeof(FXREVERB_PARAMETERS));


}

void cSound::EffectEqualizer(FXEQ_PARAMETERS EqualizerParameters)
{
	IUnknown * pXAPO;
	CreateFX(__uuidof(FXEQ), &pXAPO);

	XAUDIO2_EFFECT_DESCRIPTOR descriptor;
	descriptor.InitialState = true;
	descriptor.OutputChannels = 2;
	descriptor.pEffect = pXAPO;


	XAUDIO2_EFFECT_CHAIN chain;
	chain.EffectCount = 1;
	chain.pEffectDescriptors = &descriptor;


	pSourceVoice->SetEffectChain(&chain);

	pXAPO->Release();

	FXEQ_PARAMETERS XAPOParameters;
	XAPOParameters.FrequencyCenter0 = EqualizerParameters.FrequencyCenter0;
	XAPOParameters.Gain0 = EqualizerParameters.Gain0;
	XAPOParameters.Bandwidth0 = EqualizerParameters.Bandwidth0;

	XAPOParameters.FrequencyCenter1 = EqualizerParameters.FrequencyCenter1;
	XAPOParameters.Gain1 = EqualizerParameters.Gain1;
	XAPOParameters.Bandwidth1 = EqualizerParameters.Bandwidth1;

	XAPOParameters.FrequencyCenter2 = EqualizerParameters.FrequencyCenter2;
	XAPOParameters.Gain2 = EqualizerParameters.Gain2;
	XAPOParameters.Bandwidth2 = EqualizerParameters.Bandwidth2;

	XAPOParameters.FrequencyCenter3 = EqualizerParameters.FrequencyCenter3;
	XAPOParameters.Gain3 = EqualizerParameters.Gain3;
	XAPOParameters.Bandwidth3 = EqualizerParameters.Bandwidth3;


	pSourceVoice->SetEffectParameters(0, &XAPOParameters, sizeof(FXREVERB_PARAMETERS));
	
}

void cSound::EffectEcho(float delay, float feedback, float wetdrymix)
{
	IUnknown * pXAPO;
	CreateFX(__uuidof(FXEcho), &pXAPO);

	XAUDIO2_EFFECT_DESCRIPTOR descriptor;
	descriptor.InitialState = true;
	descriptor.OutputChannels = 2;
	descriptor.pEffect = pXAPO;


	XAUDIO2_EFFECT_CHAIN chain;
	chain.EffectCount = 1;
	chain.pEffectDescriptors = &descriptor;


	pSourceVoice->SetEffectChain(&chain);

	pXAPO->Release();

	FXECHO_PARAMETERS XAPOParameters;
	XAPOParameters.Delay = delay;
	XAPOParameters.Feedback = feedback;
	XAPOParameters.WetDryMix = wetdrymix;


	pSourceVoice->SetEffectParameters(0, &XAPOParameters, sizeof(FXREVERB_PARAMETERS));

}

cSound::~cSound()
{
	pSourceVoice->DestroyVoice();
}