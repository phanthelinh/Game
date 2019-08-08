#include "Sound.h"

Sound* Sound::instance = nullptr;

Sound* Sound::getInstance()
{
	return instance;
}

Sound::Sound(HWND hWnd)
{
	primaryBuffer = 0;
	HRESULT result;
	DSBUFFERDESC bufferDesc; //describe the buffer
	result = DirectSoundCreate8(NULL, &pDevice, NULL);

	if (FAILED(result))
	{
		std::cout << "Can not create device";
	}

	result = pDevice->SetCooperativeLevel(hWnd, DSSCL_PRIORITY); // set the cooperative level.
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = 0;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = NULL;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	result = pDevice->CreateSoundBuffer(&bufferDesc, &primaryBuffer, NULL);

	if (FAILED(result))
	{
		std::cout << "Can not create primaryBuffer";
	}
	volume = 95.0f;
	isMute = false;
	LoadResources();
}
Sound::~Sound()
{
	for (auto it = soundBufferMap.begin(); it != soundBufferMap.end(); it++)
	{
		if (it->second)
		{
			it->second->Release();
			it->second = NULL;
		}

	}

	if (primaryBuffer)
		primaryBuffer->Release();
	if (pDevice)
		pDevice->Release();
	pDevice = NULL;
	primaryBuffer = NULL;
}

void Sound::create(HWND hWnd)
{
	if (instance == nullptr)
	{
		instance = new Sound(hWnd);
	}
}

void Sound::LoadResources()
{
	this->loadSound((char*)"Resources/sound/soundtrack.wav", "soundtrack");
	this->loadSound((char*)"Resources/sound/attack.wav", "attack");
	this->loadSound((char*)"Resources/sound/jump.wav", "jump");
	this->loadSound((char*)"Resources/sound/dash.wav", "dash");
	this->loadSound((char*)"Resources/sound/bossdie.wav", "bossdie");
	this->loadSound((char*)"Resources/sound/enemydie.wav", "enemydie");
	this->loadSound((char*)"Resources/sound/item.wav", "item");
	
}

float Sound::getVolume()
{
	return volume;
}

void Sound::loadSound(char* fileName, std::string name)
{
	if (soundBufferMap.find(name) != soundBufferMap.end())
		return;
	FILE* filePtr;
	WaveHeaderStruct waveHeaderStruct;
	IDirectSoundBuffer* tempBuffer;
	DSBUFFERDESC bufferDesc;
	WAVEFORMATEX waveFormat;
	unsigned char* wavData;
	unsigned char* bufferPtr;
	unsigned long bufferSize;

	int error = fopen_s(&filePtr, fileName, "rb");
	if (error != 0)
	{
		std::cout << " Can not load " << fileName << "\n";
		return;
	}

	fread(&waveHeaderStruct, sizeof(WaveHeaderStruct), 1, filePtr);
	if ((waveHeaderStruct.format[0] != 'W') || (waveHeaderStruct.format[1] != 'A') ||
		(waveHeaderStruct.format[2] != 'V') || (waveHeaderStruct.format[3] != 'E'))
	{
		std::cout << " file format does not support" << fileName << "\n";
	}

	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = waveHeaderStruct.sampleRate;
	waveFormat.wBitsPerSample = waveHeaderStruct.bitsPerSample;
	waveFormat.nChannels = waveHeaderStruct.numChannels;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS;
	bufferDesc.dwBufferBytes = waveHeaderStruct.dataSize;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = &waveFormat;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	IDirectSoundBuffer8* secondaryBuffer = 0;
	IDirectSoundBuffer8** pSecondaryBuffer = &secondaryBuffer;

	pDevice->CreateSoundBuffer(&bufferDesc, &tempBuffer, NULL);
	auto result = tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&(*pSecondaryBuffer));

	tempBuffer->Release();
	tempBuffer = 0;

	if (FAILED(result))
	{
		std::cout << " Can not create secondaryBuffer " << "\n";
		return;
	}

	fseek(filePtr, sizeof(WaveHeaderStruct), SEEK_SET);
	wavData = new unsigned char[waveHeaderStruct.dataSize];
	fread(wavData, waveHeaderStruct.dataSize, 1, filePtr);

	error = fclose(filePtr);
	if (error != 0)
	{
		std::cout << " Can not close file " << "\n";
	}

	result = (*pSecondaryBuffer)->Lock(0, waveHeaderStruct.dataSize, (void**)&bufferPtr, (DWORD*)&bufferSize, NULL, 0, 0);

	if (FAILED(result))
	{
		return;
	}

	memcpy(bufferPtr, wavData, waveHeaderStruct.dataSize);

	(*pSecondaryBuffer)->Unlock((void*)bufferPtr, bufferSize, NULL, 0);

	if (wavData != NULL)
		delete[] wavData;

	wavData = 0;
	long tempVolume = (volume) / 100 * (-DSBVOLUME_MIN) + DSBVOLUME_MIN;
	(*pSecondaryBuffer)->SetVolume(tempVolume);
	soundBufferMap[name] = secondaryBuffer;
}


void Sound::play(std::string name, bool infiniteLoop, int times)
{
	if (isMute)
	{
		return;
	}

	std::unordered_map< std::string, IDirectSoundBuffer8*> ::iterator it;
	it = soundBufferMap.find(name);
	if (it == soundBufferMap.end()) return;

	if (infiniteLoop)
	{
		it->second->Play(0, 0, DSBPLAY_LOOPING);
	}
	else
	{
		it->second->Stop();
		it->second->SetCurrentPosition(0);
		it->second->Play(0, 0, times - 1);
	}
}

void Sound::stop(std::string name)
{
	if (name == "")
	{
		for (auto it = soundBufferMap.begin(); it != soundBufferMap.end(); it++)
		{
			it->second->Stop();
			it->second->SetCurrentPosition(0);
		}
	}
	else
	{
		std::unordered_map<std::string, IDirectSoundBuffer8*> ::iterator it;
		it = soundBufferMap.find(name);
		if (it == soundBufferMap.end())
			return;
		else
		{
			it->second->Stop();
			it->second->SetCurrentPosition(0);
		}
	}
}

void Sound::setVolume(float percentage, std::string name)
{
	volume = percentage;
	if (name == "")
	{
		long volumne = (percentage) / 100 * (-DSBVOLUME_MIN) + DSBVOLUME_MIN;
		for (auto it = soundBufferMap.begin(); it != soundBufferMap.end(); it++)
		{
			it->second->SetVolume(volumne);
		}
	}
	else
	{
		std::unordered_map< std::string, IDirectSoundBuffer8*> ::iterator it;
		it = soundBufferMap.find(name);
		if (it == soundBufferMap.end())
			return;
		long volumne = (percentage) / 100 * (-DSBVOLUME_MIN) + DSBVOLUME_MIN;
		it->second->SetVolume(volumne);
	}
}

void Sound::cleanUp()
{
	delete this;
}