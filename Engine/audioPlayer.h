#ifndef AUDIOPLAYER
#define AUDIOPLAYER


#include <string>
#include "SDL2/SDL.h"


class Audio
{
public:

	SDL_AudioDeviceID deviceId;
	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8 *wavBuffer;

	Audio(const char* filepath)
	{
		SDL_LoadWAV(filepath, &wavSpec, &wavBuffer, &wavLength);
		deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
	}


	void setAudioFile(const char* filepath)
	{
		SDL_LoadWAV(filepath, &wavSpec, &wavBuffer, &wavLength);
		deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
	}


	void play(bool play)
	{
		SDL_QueueAudio(deviceId, wavBuffer, wavLength);
		SDL_PauseAudioDevice(deviceId, !play);
	}

	
};




#endif