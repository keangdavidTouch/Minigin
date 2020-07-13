#pragma once
#include "Observer.h"
#include "Subject.h"

namespace kd
{
	class GameObject;

	class HealthDisplay : public Observer
	{
	public:

		enum EventType { Pump, Dig, Rock };

		HealthDisplay(GameObject* textObject);
		~HealthDisplay() = default;
		void OnNotify(int event, GameObject* object) override;

	private:
		Subject m_Subject;
		GameObject* m_TextObject;
	};
}

