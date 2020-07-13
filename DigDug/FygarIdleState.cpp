#include "pch.h"
#include "WanderState.h"
#include "FygarBehaviour.h"
#include "GetPumpedState.h"
#include "SpitFireCommand.h"
#include "FygarFireState.h"

kd::BaseState* kd::WanderState::HandleInput(GameObject* object, const BaseCommand* command)
{
	if (object->GetComponent<FygarBehaviour>()->GetPumped())
	{
		return new GetPumpedState();
	}
	else if (object->GetComponent<FygarBehaviour>()->GetRocked())
	{
		return new FygarDieState();
	}

	if (command != nullptr)
	{
		if (typeid(*command).name() ==  typeid(SpitFireCommand).name())
			return new FygarFireState();
	}

	return nullptr;
}

void kd::WanderState::Update(GameObject* )
{

}
void kd::WanderState::Enter(GameObject* object)
{
	object->GetComponent<SpriteComponent>()->SetCurrentClip(0);
	std::cout << "Enter Fygar-IdleState" << std::endl;
}

void kd::WanderState::Exit(GameObject* )
{
}
