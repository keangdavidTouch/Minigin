#pragma once
#include "Singleton.h"
#include <glm/vec2.hpp>
#include <memory>

namespace kd
{
	class Cell;

	class PathFinder final : public Singleton<PathFinder>
	{
	public:
		PathFinder();
		~PathFinder() = default;
		void Init(unsigned short nrOfCol, unsigned short nrOfRow, int gridSize);
		std::vector<glm::vec2> FindPath(unsigned short  fromCol, unsigned short  fromRow, unsigned short  toCol, unsigned short  toRow);
		void ResetNodes();
		void SetCellAsBlock(int row, int col, bool block = true);
		bool SetCellAtPoAsBlock(int y, int x, bool block);
		bool IsCellBlock(int row, int col) const;
		bool IsCellAtPosBlock(int y, int x) const;
		unsigned short NumberOfCol() const { return m_NrOfCol; }
		unsigned short NumberOfRow() const { return m_NrOfRow; }

		void DebugRenderCellGrids();
		void DebugRenderPath();

	private:

		int m_GridSize;
		unsigned short m_NrOfCol;
		unsigned short m_NrOfRow;
		unsigned short m_StartRow;
		unsigned short m_StartCol;
		std::vector<glm::vec2> m_Paths;

		Cell* m_Startcell;
		Cell* m_TargetCell;
		std::vector<Cell*> m_OpenList;
		std::vector<Cell*> m_CloseList;
		std::vector<std::vector<std::shared_ptr<Cell>>> m_AllNodes;
		bool IsValidCell(int col, int row) const;
	};
}


