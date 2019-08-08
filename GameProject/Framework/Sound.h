#pragma once
#include "dsound.h"
#include "windows.h"
#include <unordered_map>
#include <string>
#include <iostream>
#include <mmsystem.h>
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

#define SOUND	Sound::getInstance()

class Sound
{
public:
	struct WaveHeaderStruct
	{
		char chunkId[4];
		unsigned long chunkSize;
		char format[4];
		char subChunkId[4];
		unsigned long subChunkSize;
		unsigned short audioFormat;
		unsigned short numChannels;
		unsigned long sampleRate;
		unsigned long bytesPerSecond;
		unsigned short blockAlign;
		unsigned short bitsPerSample;
		char dataChunkId[4];
		unsigned long dataSize;
	};

	float volume;
	void static create(HWND hWnd);
	void LoadResources();
	void setVolume(float percentage, std::string name = "");
	void loadSound(char* fileName, std::string name);
	void play(std::string name, bool infiniteLoop = false, int times = 1);
	void stop(std::string name = "");
	float getVolume();
	~Sound();
	static Sound* getInstance();
	bool isMute;
	void unMute();
	void cleanUp();

private:
	Sound(HWND hWnd);
	static Sound * instance;
	IDirectSound8* pDevice;
	IDirectSoundBuffer* primaryBuffer;
	std::unordered_map<std::string, IDirectSoundBuffer8*> soundBufferMap;
};
