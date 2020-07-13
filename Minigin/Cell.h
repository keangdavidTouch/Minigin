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
		Cell() = default;
		~Cell() = default;
		Cell(int col, int row) : m_Col(col), m_Row(row)
		{
			m_Pos = glm::vec2(float(m_Col) * SIZE, float(m_Row) * SIZE);
		};
		bool IsBlock() const { return m_IsBlock; };
		void SetAsBlock(bool block) { m_IsBlock = block; };
		float GetFCost() const { return m_FCost; };
		float GetGCost() const { return m_GCost; };
		float GetHCost() const { return m_HCost; };
		void SetGCost(float cost) { m_GCost = cost; };
		void SetFCost(float cost) { m_FCost = cost; };
		void SetHCost(float cost) { m_HCost = cost; };
		
		void SetParent(Cell* parent) { m_ParentCell = parent; };
		Cell* GetParent() const { return m_ParentCell; };
		
		std::vector<Cell*> GetConnections() const { return m_Connections; };
		void AddConnection(Cell* cell) { m_Connections.push_back(cell); };
		
		glm::vec2 GetPosition() const { return m_Pos; };

		void Reset()
		{
			m_GCost = std::numeric_limits<float>::max();
			m_HCost = std::numeric_limits<float>::max();
			m_FCost = 0.f;
			m_ParentCell = nullptr;
		}

	private:
		int m_Col = 0;
		int m_Row = 0;
		
		float m_GCost = std::numeric_limits<float>::max();
		float m_HCost = std::numeric_limits<float>::max();
		float m_FCost = 0.f;

		glm::vec2 m_Pos = glm::vec2();
		Cell* m_ParentCell = nullptr;
		std::vector<Cell*> m_Connections;
		bool m_IsBlock = false;

		static const int SIZE = 16 * 3;
	};
}



