#include "MiniginPCH.h"
#include "PathFinder.h"
#include "Cell.h"
#include <algorithm>

kd::PathFinder::PathFinder()
	: m_Startcell()
	, m_TargetCell()
	, m_CloseList()
	, m_OpenList()
	, m_NrOfCol(0)
	, m_NrOfRow(0)
	, m_GridSize(1)
{
}

void kd::PathFinder::Init(unsigned short nrOfCol, unsigned short nrOfRow, int gridSize)
{
	m_NrOfCol = nrOfCol;
	m_NrOfRow = nrOfRow;
	m_GridSize = gridSize;

	for (int row  = 0; row < m_NrOfRow; row++)
	{
		m_AllNodes.push_back(std::vector<std::shared_ptr<Cell>>());

		for (int col  = 0; col < m_NrOfCol; col++)
		{
			m_AllNodes[row].push_back(std::make_shared<Cell>(col, row, GetCellPosition(col, row)));
		}	
	}

	for (int row  = 0; row < m_NrOfRow; row++)
	{
		for (int col  = 0; col < m_NrOfCol; col++)
		{
			auto cell = m_AllNodes[row][col];

			// Top
			if (IsValidCell(col, row + 1))
				cell->AddConnection(m_AllNodes[row + 1][col].get());
			// Down
			if (IsValidCell(col, row - 1))
				cell->AddConnection(m_AllNodes[row - 1][col].get());
			// Right
			if (IsValidCell(col + 1, row))
				cell->AddConnection(m_AllNodes[row][col + 1].get());
			// Left
			if (IsValidCell(col - 1, row))
				cell->AddConnection(m_AllNodes[row][col - 1].get());
		}	
	}

	for (int row  = 0; row < m_NrOfRow; row++)
	{
		for (int col  = 0; col < m_NrOfCol; col++)
		{
			auto cell = m_AllNodes[row][col];
			cell->SetAsBlock(true);
		}	
	}
}

void kd::PathFinder::ResetNodes()
{
	if (!m_AllNodes.empty())
	{
		for (int row  = 0; row < m_NrOfRow; row++)
		{
			for (int col  = 0; col < m_NrOfCol; col++)
			{
				m_AllNodes[row][col]->Reset();
			}	
		}

		return;
	}
}

void kd::PathFinder::FindPath(std::vector<glm::vec2>& paths, unsigned short fromCol, unsigned short fromRow, unsigned short  toCol, unsigned short  toRow)
{
	m_StartCol = fromCol;
	m_StartRow = fromRow;

	// Setup Before Start Finding Path
	paths.clear();
	m_OpenList.clear();
	m_CloseList.clear();

	m_Startcell = m_AllNodes[fromRow][fromCol].get();
	m_TargetCell = m_AllNodes[toRow][toCol].get();

	auto currentCell = m_Startcell;
	currentCell->SetGCost(0);
	currentCell->SetHCost(GetHCost(m_Startcell, m_TargetCell));

	m_OpenList.push_back(m_Startcell);

	while(!m_OpenList.empty() && currentCell != m_TargetCell)
	{
		auto pred = [](Cell* a, Cell* b) { return a->GetFCost() < b->GetFCost(); }; 
		currentCell = *std::min_element(m_OpenList.begin(), m_OpenList.end(), pred);

		m_OpenList.erase(remove(m_OpenList.begin(), m_OpenList.end(), currentCell));
		m_CloseList.push_back(currentCell);

		for(auto cell : currentCell->GetConnections())
		{
			// if not visit yet
			if (std::find(m_CloseList.begin(), m_CloseList.end(), cell) == m_CloseList.end()) 
			{
				float tempG = currentCell->GetGCost() + GetDistance(currentCell, cell);

				if (std::find(m_OpenList.begin(), m_OpenList.end(), cell) == m_OpenList.end() && cell->IsBlock() == false)
					m_OpenList.push_back(cell);
				else if (tempG >= cell->GetGCost())
					continue;

				cell->SetGCost(tempG);
				cell->SetHCost(GetDistance(currentCell, m_TargetCell));
				cell->SetFCost(cell->GetGCost() + cell->GetHCost());
				cell->SetParent(currentCell);
			}
		}
	}

	// Reconstruct Path
	if(m_TargetCell != nullptr)
	{
		auto temp = m_TargetCell;
		paths.push_back(temp->GetPosition());
		while(temp->GetParent() != nullptr)
		{
			temp = temp->GetParent();
			paths.push_back(temp->GetPosition());
		}

		if (!paths.empty())
			paths.pop_back();
	}
}

float kd::PathFinder::GetDistance(Cell * a, Cell * b)
{
	auto aPos = a->GetPosition();
	auto bPos = b->GetPosition();
	return sqrtf((aPos.x - bPos.x)*(aPos.x - bPos.x) + (aPos.y - bPos.y)*(aPos.y - bPos.y));
}

float kd::PathFinder::GetHCost(Cell * a, Cell * b)
{
	return GetDistance(a, b);
}

void kd::PathFinder::SetCellAsBlock(int row, int col, bool block)
{
	m_AllNodes[row][col]->SetAsBlock(block);
}

bool kd::PathFinder::SetCellAtPoAsBlock(int y, int x, bool block)
{
	int row = y / m_GridSize;
	int col = x / m_GridSize;
	if(row >= m_NrOfRow || col >= m_NrOfCol || row < 0 || col < 0) return false;
	m_AllNodes[row][col]->SetAsBlock(block);
	return true;
}

bool kd::PathFinder::IsCellAtPosBlock(int y, int x) const
{
	int row = y / m_GridSize;
	int col = x / m_GridSize;
	if(row >= m_NrOfRow || col >= m_NrOfCol || row < 0 || col < 0) return false;
	return m_AllNodes[row][col]->IsBlock();
}

bool kd::PathFinder::IsCellBlock(int row, int col) const
{
	return m_AllNodes[row][col]->IsBlock();
}

bool kd::PathFinder::IsValidCell(int col, int row) const
{
	bool validIndex = (col < m_NrOfCol && col >= 0) && (row < m_NrOfRow && row >= 0);
	if (validIndex)
		if(m_AllNodes[row][col])
			return !m_AllNodes[row][col]->IsBlock();

	return validIndex;
}

glm::vec2 kd::PathFinder::GetCellPosition(int cols, int rows) const
{
	return glm::vec2(float(cols * m_GridSize), float(rows * m_GridSize));
}
