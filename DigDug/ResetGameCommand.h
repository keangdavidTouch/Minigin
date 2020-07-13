#include "BaseCommand.h"
#include "SceneManager.h"

namespace kd
{
	class SwitchToVersusMode final : public BaseCommand
	{
	public:

		void Execute() override {
			SceneManager::GetInstance().GoNextScene();
		}

	private:

	};
}

