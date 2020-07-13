#pragma once
#include "Audio.h"
#include "NullAudio.h"
#include "ConsoleAudio.h"
#include "LoggedAudio.h"

class ServiceLocator
{
public:
	static void init() { 
		audioService = &defaultAudioService; 
	};

	static Audio& GetAudio() { 
		return *audioService; 
	};

	static void RegisterAudioService(Audio* service) {
		Destroy();
		audioService = (service == nullptr) ? &defaultAudioService : service;
	}

	static void Destroy()
	{
		if (audioService != &defaultAudioService)
			SafeDelete(audioService);
	}

private:
	static Audio* audioService;
	static NullAudio defaultAudioService;
};

