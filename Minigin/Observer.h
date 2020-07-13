#pragma once
#include "../Minigin/GameObject.h"

namespace kd
{
	class Observer
	{
	public:
		Observer() = default;
		virtual ~Observer() {}
		virtual void OnNotify(int event, GameObject* gameObject) = 0;
	private:
	};
}


