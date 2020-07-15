#pragma once
#include "BaseComponent.h"
#include "PathFinder.h"

namespace kd
{
	class AIComponent final : public BaseComponent
	{
	public:
		AIComponent(GameObject* target, float gridSize, bool enable = true);
		~AIComponent() = default;

		void Initialize() override;
		void Update() override;
		void Render() const override;
		void SetEnable(bool enable);
		bool NoAvailablePath() ;
		GameObject* GetTarget() const { return m_Target; };

	private:
		bool CalculatePath();
		bool m_NoAvailablePath = false;
		bool m_Enable = true;
		bool m_InitialAIMode = true;
		const float m_GridSize;
		const float m_Speed = 1.f;
		GameObject* m_Target;
		std::vector<glm::vec2> m_Paths;
	};
}


