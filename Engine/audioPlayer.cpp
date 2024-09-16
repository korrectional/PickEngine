
#include "audioPlayer.h"




Audio::Audio(const char* filepath)
{
	SDL_LoadWAV(filepath, &wavSpec, &wavBuffer, &wavLength);
	deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
}


void Audio::setAudioFile(const char* filepath)
{
	SDL_LoadWAV(filepath, &wavSpec, &wavBuffer, &wavLength);
	deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
}


void Audio::play()
{
	
	SDL_QueueAudio(deviceId, wavBuffer, wavLength);
	SDL_PauseAudioDevice(deviceId, 0);
}

void Audio::stopSound()
{
	SDL_PauseAudioDevice(deviceId, 1);
}



