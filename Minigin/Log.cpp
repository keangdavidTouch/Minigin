#include "MiniginPCH.h"
#include "Log.h"
#include <iostream>


std::basic_streambuf<char>::int_type kd::DebugStreambuf::overflow(int_type c)
{
	if (c != EOF)
	{
		char buf[] = {static_cast<char>(c), '\0'};
		OutputDebugStringA(buf);
	}
	return c;
}

kd::Cout2VisualStudioDebugOutput::Cout2VisualStudioDebugOutput()
{
	default_stream = std::cout.rdbuf(&dbgstream);
}

kd::Cout2VisualStudioDebugOutput::~Cout2VisualStudioDebugOutput()
{
	std::cout.rdbuf(default_stream);
}
