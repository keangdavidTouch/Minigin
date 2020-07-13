#include "pch.h"
#include "PoogaBehaviour.h"

kd::PookaBehaviour::PookaBehaviour(GameObject* player) 
	: EnemyBehaviour(player, SpriteInfo(1, SDL_Rect{103, 33, 32, 24}, 0, 0, 0.4f))
{
}
