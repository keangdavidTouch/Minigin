#pragma once
#include "Audio.h"

class ConsoleAudio : public Audio
{
public:
	ConsoleAudio();
	~ConsoleAudio() override;
	void PlaySound(int soundId) override;
	void StopSound(int soundId) override;
	void StopAllSounds() override;

private:
	Mix_Chunk* m_Chunk;
};

