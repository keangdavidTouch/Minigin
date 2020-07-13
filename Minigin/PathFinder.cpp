#include "MiniginPCH.h"
#include "PathFinder.h"
#include "Cell.h"
#include <algorithm>
#include "Renderer.h"
#include <SDL.h>

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
			m_AllNodes[row].push_back(std::make_shared<Cell>(col, row));
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

std::vector<glm::vec2> kd::PathFinder::FindPath(unsigned short fromCol, unsigned short fromRow, unsigned short  toCol, unsigned short  toRow)
{
	m_StartCol = fromCol;
	m_StartRow = fromRow;

	// Setup Before Start Finding Path
	m_OpenList.clear();
	m_CloseList.clear();

	m_Startcell = m_AllNodes[fromRow][fromCol].get();
	m_TargetCell = m_AllNodes[toRow][toCol].get();

	auto distance = [](Cell* a, Cell* b) // For convenience
	{
		auto aPos = a->GetPosition();
		auto bPos = b->GetPosition();
		return sqrtf((aPos.x - bPos.x)*(aPos.x - bPos.x) + (aPos.y - bPos.y)*(aPos.y - bPos.y));
	};

	auto heuristic = [distance](Cell* a, Cell* b) // So we can experiment with heuristic
	{
		return distance(a, b);
	};

	auto currentCell = m_Startcell;
	currentCell->SetGCost(0);
	currentCell->SetHCost(heuristic(m_Startcell, m_TargetCell));

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
				float tempG = currentCell->GetGCost() + distance(currentCell, cell);

				if (std::find(m_OpenList.begin(), m_OpenList.end(), cell) == m_OpenList.end() && cell->IsBlock() == false)
					m_OpenList.push_back(cell);
				else if (tempG >= cell->GetGCost())
					continue;

				cell->SetGCost(tempG);
				cell->SetHCost(distance(currentCell, m_TargetCell));
				cell->SetFCost(cell->GetGCost() + cell->GetHCost());
				cell->SetParent(currentCell);
			}
		}
	}

	std::vector<glm::vec2> paths{};

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

	m_Paths = paths;
	return paths;
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

#pragma region DEBUG_RENDERING

void kd::PathFinder::DebugRenderCellGrids()
{
	int x, y;
	if (SDL_MOUSEBUTTONUP && SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_MIDDLE)) //SDL_MOUSEBUTTONDOWN
	{
		auto node = m_AllNodes[y / m_GridSize][x / m_GridSize];
		node->SetAsBlock(false);
	}

	int drawSize = m_GridSize - 1;
	SDL_Rect rect{0, 0, drawSize, drawSize};

	for (int row  = 0; row < m_NrOfRow; row++)
	{
		for (int col  = 0; col < m_NrOfCol; col++)
		{
			auto pos = m_AllNodes[row][col]->GetPosition();
			rect.x = int(pos.x);
			rect.y = int(pos.y);

			SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(),0, 0, 0, 0);

			if(m_AllNodes[row][col]->IsBlock())
				SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(),255, 255, 255, 0);
			if (row == m_NrOfRow - 1 && col == m_NrOfCol - 1)
				SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(),0, 255, 0, 0);

			SDL_RenderFillRect(Renderer::GetInstance().GetSDLRenderer(), &rect);
		}
	}
}

void kd::PathFinder::DebugRenderPath()
{
	//#DEBUG
	if(m_Paths.size() < 1) 
		return;

	/*SDL_Rect startRect{0, 0, m_GridSize, m_GridSize};
	startRect.x = m_StartCol * m_GridSize;
	startRect.y = m_StartRow * m_GridSize;
	SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(),255, 0, 0, 0);
	SDL_RenderDrawRect(Renderer::GetInstance().GetSDLRenderer(), &startRect);*/

	/*int offset = 40;
	int halfOffset = offset/2;
	int drawSize = m_GridSize - offset;
	SDL_Rect rect{0, 0, drawSize, drawSize};

	for (size_t i  = 1; i < m_Paths.size(); i++)
	{
		auto pos = m_Paths[i];
		rect.x = int(pos.x) + halfOffset;
		rect.y = int(pos.y) + halfOffset;

		SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(),0, 255, 0, 0);
		SDL_RenderFillRect(Renderer::GetInstance().GetSDLRenderer(), &rect);
	}*/
}

#pragma endregion
