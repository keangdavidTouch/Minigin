#pragma once

namespace kd
{
	class BaseState;
	class GameObject;

	class StateMachine final
	{
	public:
		StateMachine(BaseState* initialState);
		~StateMachine();

		void Initialize(GameObject* gameObject);
		void Update(GameObject* gameobject);
	private:
		BaseState* m_CurrentState;
	};
}



