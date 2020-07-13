#pragma once
#include "SDL_mixer.h"

class Audio {

public:
	virtual void PlaySound(int soundId) = 0;
	virtual void StopSound(int soundId) = 0;
	virtual void StopAllSounds() = 0;
	virtual ~Audio(){};
};