#include "MiniginPCH.h"
#include "LoggedAudio.h"
#include <iostream>

LoggedAudio::LoggedAudio(Audio* audio)
	: m_Audio{ audio }
	, m_LoggedString{""}
{
}

void LoggedAudio::PlaySound(int soundId)
{
	m_Audio->PlaySound(soundId);
	Logged(__func__);
}

void LoggedAudio::StopSound(int soundId)
{
	m_Audio->StopSound(soundId);
	Logged(__func__);
}

void LoggedAudio::StopAllSounds()
{
	m_Audio->StopAllSounds();
	Logged(__func__);
}

void LoggedAudio::Logged(const std::string& text)
{
	m_LoggedString = text;
	std::cout << m_LoggedString << std::endl;
}

std::string & LoggedAudio::GetLoggedText()
{
	return m_LoggedString;
}


