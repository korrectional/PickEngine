#ifndef AUDIOPLAYER
#define AUDIOPLAYER


#include <string>
#include "SDL2/SDL.h"

void playSound(const char* filepath)
{
    //std::cout<<SDL_GetError()<<"\n";
	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8 *wavBuffer;
	SDL_LoadWAV(filepath, &wavSpec, &wavBuffer, &wavLength);
	SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
	SDL_QueueAudio(deviceId, wavBuffer, wavLength);
    SDL_GetError();
	SDL_PauseAudioDevice(deviceId, 0);
}


#endif