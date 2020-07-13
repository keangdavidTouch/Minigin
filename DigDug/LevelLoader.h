#pragma once
#include <string>
#include <fstream>
#include <istream>

namespace kd
{
	class LevelLoader
	{
	public:
		LevelLoader() = default;
		~LevelLoader() = default;

		void ReadBinary(const std::string& filename);
		void WriteBinary(const std::string& filename);
	private:
	};
}