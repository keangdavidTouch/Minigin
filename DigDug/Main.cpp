#include "pch.h"
#include <vld.h>
#include "DigDugGame.h"

#pragma warning( push )  
#pragma warning( disable : 4100 )  
int main(int argc, char* argv[]) {
#pragma warning( pop )

	auto gameSetting = kd::GameSetting(672,768, "DigDug", "../Resources/");

	kd::DigDugGame engine(gameSetting);
	engine.Run();
	return 0;
}

