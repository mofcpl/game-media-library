#include"DirectX_11-Audio.h"

cAudio::cAudio()
{
	//CoInitializeEx(NULL, COINIT_MULTITHREADED);

	hr = XAudio2Create( &pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR );
	CheckError(hr,L"xAudio2Create");

	hr = pXAudio2->CreateMasteringVoice( &pMasterVoice, XAUDIO2_DEFAULT_CHANNELS,XAUDIO2_DEFAULT_SAMPLERATE, 0, 0, NULL );
	CheckError(hr,L"CreateMasteringVoice");


}

void cAudio::Load(const char* path, cSound* wave)
{
	HRESULT hr;
	
	hr=wave->buffer->load( path );
	CheckError(hr, L"CreateSourceVoice");

	hr = pXAudio2->CreateSourceVoice(&wave->pSourceVoice, wave->buffer->wf(), XAUDIO2_VOICE_USEFILTER);
	CheckError(hr, L"CreateSourceVoice");

}

void cAudio::Start(cSound* wave)
{
	wave->pSourceVoice->Start(0,0);
}

void cAudio::Stop(cSound* wave)
{
	wave->pSourceVoice->Stop(0, 0);
}

void cAudio::Submit(cSound* wave)
{	
	wave->pSourceVoice->SubmitSourceBuffer(wave->buffer->xaBuffer());
}

void cAudio::Flush(cSound* wave)
{
	wave->pSourceVoice->FlushSourceBuffers();
}

cAudio::~cAudio()
{
	pMasterVoice->DestroyVoice();
	pXAudio2->Release();

	//CoUninitialize();
}
