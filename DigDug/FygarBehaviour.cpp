#include "pch.h"
#include "FygarBehaviour.h"
#include "DigDugGame.h"

kd::FygarBehaviour::FygarBehaviour(GameObject* fire, GameObject* player) 
	: EnemyBehaviour(player, SpriteInfo(1, SDL_Rect{120, 58, 32, 24}, 0, 0, 0.4f))
	, m_Flame(fire)
{
}

kd::FygarBehaviour::~FygarBehaviour()
{
	if(m_Flame->GetParent() == nullptr)
		SafeDelete(m_Flame);
}

void kd::FygarBehaviour::AddFlame()
{
	GetGameObject()->AddChild(m_Flame);
}

void kd::FygarBehaviour::RemoveFlame()
{
	GetGameObject()->RemoveChild(m_Flame);
}

void kd::FygarBehaviour::HandleAttack()
{
	const auto offset = DigDugGame::GetGameContext().GridSize * 2;
	const auto currentPos =  GetGameObject()->GetTransform().GetPosition();
	const auto targetPos = m_Player->GetTransform().GetPosition();
	auto distance = glm::abs(targetPos.x - currentPos.x);

	if(distance <= offset && currentPos.y == targetPos.y)
		m_AttackState = EnemyBehaviour::AttackState::Fire;
	else 
		m_AttackState = EnemyBehaviour::AttackState::None;
}

