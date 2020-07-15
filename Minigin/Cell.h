#pragma once
#include "MiniginPCH.h"
#include "Vector2.h"
#include <limits>

namespace kd
{
	#undef max

	class Cell final 
	{
	public:
		Cell(int col, int row, glm::vec2 pos) : m_Col(col), m_Row(row), m_Pos(pos) {};
		~Cell() = default;
		bool IsBlock() const { return m_IsBlock; };
		void SetAsBlock(bool block) { m_IsBlock = block; };
		void SetGCost(float cost) { m_GCost = cost; };
		float GetGCost() const { return m_GCost; };
		void SetFCost(float cost) { m_FCost = cost; };
		float GetFCost() const { return m_FCost; };
		void SetHCost(float cost) { m_HCost = cost; };
		float GetHCost() const { return m_HCost; };
		void SetParent(Cell* parent) { m_ParentCell = parent; };
		Cell* GetParent() const { return m_ParentCell; };
		glm::vec2 GetPosition() const { return m_Pos; };

		void AddConnection(Cell* cell) { m_Connections.push_back(cell); };
		std::vector<Cell*> GetConnections() const { return m_Connections; };

		void Reset()
		{
			m_GCost = std::numeric_limits<float>::max();
			m_HCost = std::numeric_limits<float>::max();
			m_FCost = 0.f;
			m_ParentCell = nullptr;
		}

	private:
		bool m_IsBlock = false;
		int m_Col = 0;
		int m_Row = 0;
		float m_GCost = std::numeric_limits<float>::max();
		float m_HCost = std::numeric_limits<float>::max();
		float m_FCost = 0.f;
		Cell* m_ParentCell = nullptr;
		glm::vec2 m_Pos = glm::vec2();
		std::vector<Cell*> m_Connections;
	};
}



