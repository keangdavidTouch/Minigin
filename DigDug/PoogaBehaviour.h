#pragma once
#include "EnemyBehaviour.h" 

namespace kd
{
	class PookaBehaviour final : public EnemyBehaviour 
	{
		public:
		PookaBehaviour(GameObject* player); 
		~PookaBehaviour() = default;
	};
}

