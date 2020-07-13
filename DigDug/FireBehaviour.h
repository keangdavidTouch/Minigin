#pragma once
#include "BaseComponent.h"

namespace kd
{
	class PumpBehaviour final : public BaseComponent 
	{
	public:
		PumpBehaviour() = default; 
		~PumpBehaviour() = default;
		//static void TriggerEnter(GameObject* other);

		void Initialize() override;
		void Update() override;
		void Render() const override;
	private:
	};
}

