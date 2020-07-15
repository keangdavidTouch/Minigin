#pragma once
#include "Singleton.h"

namespace kd
{
	class Cell;

	class PathFinder final : public Singleton<PathFinder>
	{
	public:
		PathFinder();
		~PathFinder();
		void Init(unsigned short nrOfCol, unsigned short nrOfRow, int gridSize);
		void ResetNodes();
		void FindPath(std::vector<glm::vec2>& paths, unsigned short  fromCol, unsigned short  fromRow, unsigned short  toCol, unsigned short  toRow);
		void SetCellAsBlock(int row, int col, bool block = true);
		bool SetCellAtPoAsBlock(int y, int x, bool block);
		bool IsCellBlock(int row, int col) const;
		bool IsCellAtPosBlock(int y, int x) const;
		glm::vec2 GetCellPosition(int cols, int rows) const; 
		unsigned short NumberOfCol() const { return m_NrOfCol; }
		unsigned short NumberOfRow() const { return m_NrOfRow; }

	private:
		int m_GridSize;
		unsigned short m_NrOfCol;
		unsigned short m_NrOfRow;
		unsigned short m_StartRow;
		unsigned short m_StartCol;
		Cell* m_Startcell;
		Cell* m_TargetCell;
		std::vector<Cell*> m_OpenList;
		std::vector<Cell*> m_CloseList;
		std::vector<std::vector<Cell*>> m_AllNodes;
		bool IsValidCell(int col, int row) const;
		float GetDistance(Cell* a, Cell* b) const;
	};
}


