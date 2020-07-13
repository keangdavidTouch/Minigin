#include "MiniginPCH.h"
#include "StateMachine.h"
#include "GameObject.h"
#include "BaseState.h"

kd::StateMachine::StateMachine(BaseState * initialState)
	: m_CurrentState(initialState)
{
}

kd::StateMachine::~StateMachine()
{
	SafeDelete(m_CurrentState);
}

void kd::StateMachine::Initialize(GameObject * gameObject)
{
	m_CurrentState->Enter(gameObject);
}

void kd::StateMachine::Update(GameObject * gameobject)
{
	BaseState* state = m_CurrentState->Update(gameobject);

	if (state != nullptr)
	{
		m_CurrentState->Exit(gameobject);
		delete m_CurrentState;
		m_CurrentState = state;
		m_CurrentState->Enter(gameobject);
	}
}


