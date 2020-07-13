#include "MiniginPCH.h"
#include "ConsoleAudio.h"
#include <iostream>

ConsoleAudio::ConsoleAudio()
{
	if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) != -1)
		std::cout << "Open Audio Device..." << std::endl;
	else
		std::cout << "Unable to open audio device. Mix_GetError: " << Mix_GetError() << std::endl;
}

ConsoleAudio::~ConsoleAudio()
{
	Mix_FreeChunk(m_Chunk);
}

void ConsoleAudio::PlaySound(int soundId)
{
	std::string filePath{"../Resources/"};

	switch (soundId)
	{
	case 0: filePath += "fire.wav"; break;
	case 1: filePath += "jump.wav"; break;
	case 2: filePath += "fart.wav"; break;
	case 3: filePath += "duck.wav"; break;
	default:
		filePath += "fire.wav"; break;
	}
	m_Chunk = Mix_LoadWAV(filePath.c_str());
	if (m_Chunk) Mix_PlayChannel(-1,m_Chunk,0);
}

void ConsoleAudio::StopSound(int)
{
	Mix_Pause(-1);
}

void ConsoleAudio::StopAllSounds()
{
	Mix_CloseAudio();
}
