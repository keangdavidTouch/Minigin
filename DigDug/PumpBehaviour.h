#pragma once
#include "BaseComponent.h"

namespace kd
{
	class TaizoBehaviour;
	struct CollisionHit;

	class PumpBehaviour final : public BaseComponent 
	{
	public:
		PumpBehaviour() = default; 
		~PumpBehaviour() = default;
		void TriggerEnter(CollisionHit* hit);

		void Initialize() override;
		void Update() override;
		void Render() const override;
	private:
		TaizoBehaviour* m_PlayerComponent;
	};
}

