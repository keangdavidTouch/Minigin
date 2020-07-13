#pragma once
#include "BaseComponent.h"

namespace kd
{
	class TextComponent;

	class FpsComponent final : public BaseComponent 
	{
	public:
		FpsComponent();
		~FpsComponent();

		void Initialize() override;
		void Update() override;
		void Render() const override;
	private:
		TextComponent* m_TextComponent;
	};
}

