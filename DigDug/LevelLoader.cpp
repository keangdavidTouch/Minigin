#include "pch.h"
#include "LevelLoader.h"
#include "PathFinder.h"

void kd::LevelLoader::ReadBinary(const std::string & filename)
{
	std::ifstream inFile(filename, std::ios::out | std::ios::binary);
	
	if (inFile.fail()) {
		std::cerr << "Could not open Path file " << filename << '\n';
		return;
	}

	unsigned short rows = 0;
	unsigned short cols = 0;
	inFile.read(reinterpret_cast<char*>(&rows), sizeof(short));
	inFile.read(reinterpret_cast<char*>(&cols), sizeof(short));

	for(unsigned short i = 0; i < rows; i++)
	{
		for(unsigned short j = 0; j < cols; j++)
		{
			unsigned short c;
			inFile.read(reinterpret_cast<char*>(&c), sizeof(short));
			PathFinder::GetInstance().SetCellAsBlock(i, j, c!=0);
		}
	}
}

void kd::LevelLoader::WriteBinary(const std::string & filename)
{
	unsigned short cols = PathFinder::GetInstance().NumberOfCol();
	unsigned short rows = PathFinder::GetInstance().NumberOfRow();

	std::ofstream outFile(filename, std::ios::out | std::ios::binary);

	outFile.write(reinterpret_cast<char*>(&rows), sizeof(short));
	outFile.write(reinterpret_cast<char*>(&cols), sizeof(short));

	for(short i = 0; i < rows; i++)
	{
		for(short j = 0; j < cols; j++)
		{
			unsigned short isBlocked = PathFinder::GetInstance().IsCellBlock(i, j);
			outFile.write(reinterpret_cast<char*>(&isBlocked), sizeof(short));
		}
	}

	outFile.close();
}
