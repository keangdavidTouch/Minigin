#pragma once
#include <streambuf>

namespace kd
{
	class DebugStreambuf : public std::streambuf 
	{
	public:
		int_type overflow(int_type c) override;
	};

	// This class redirects the output of std::cout to the visual studio debug stream
	// https://gist.github.com/takashyx/937f3a794ad36cd98ec3
	class Cout2VisualStudioDebugOutput 
	{
		DebugStreambuf dbgstream;
		std::streambuf *default_stream{};

	public:
		Cout2VisualStudioDebugOutput();
		~Cout2VisualStudioDebugOutput();

		Cout2VisualStudioDebugOutput(const Cout2VisualStudioDebugOutput &) = delete;
		Cout2VisualStudioDebugOutput(Cout2VisualStudioDebugOutput &&) = delete;
		Cout2VisualStudioDebugOutput & operator= (const Cout2VisualStudioDebugOutput &) = delete;
		Cout2VisualStudioDebugOutput & operator= (const Cout2VisualStudioDebugOutput &&) = delete;
	};

#ifdef _DEBUG
#ifdef _MSC_VER
	Cout2VisualStudioDebugOutput c2v;
#endif
#endif
}
