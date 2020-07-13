#pragma once
#include "Audio.h"

class NullAudio final : public Audio {

public:
	void PlaySound(int soundId) override;
	void StopSound(int soundId) override;
	void StopAllSounds() override;
};