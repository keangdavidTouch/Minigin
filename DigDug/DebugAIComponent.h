#pragma once
#include <SDL.h> // try to get rid of this
#include "BaseComponent.h"
#include "Vector2.h"

namespace kd
{
	class DebugAIComponent final : public BaseComponent 
	{
	public:
		DebugAIComponent(GameObject* object) : m_FindObject(object){};
		~DebugAIComponent() = default;

		void Initialize() override;
		void Update() override;
		void Render() const override;
	private:
		SDL_Rect m_StartNode;
		std::vector<glm::vec2> m_Paths;
		bool m_ClickStart = false;

		static const int SIZE = 16 * 3;
		static const int DRAWIZE = SIZE - 1;
		GameObject* m_FindObject;
	};
}

