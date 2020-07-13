#pragma once
#include "Audio.h"
#include <string>

class LoggedAudio : public Audio
{
public:
	~LoggedAudio() override = default;
	LoggedAudio(Audio* audio);
	void PlaySound(int soundId) override;
	void StopSound(int soundId) override;
	void StopAllSounds() override;
	void Logged(const std::string& text);
	std::string& GetLoggedText(); // FOR-UNIT-TEST
private:
	Audio* m_Audio;
	std::string m_LoggedString;
};

