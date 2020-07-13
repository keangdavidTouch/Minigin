#pragma once
#include "BaseComponent.h"

namespace kd
{
	class DebugComponent final : public BaseComponent 
	{
	public:
		DebugComponent(); 
		~DebugComponent();

		void Initialize() override;
		void Update() override;
		void Render() const override;
	private:
	};
}

