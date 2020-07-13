#include "BaseCommand.h"
#include "SceneManager.h"

namespace kd
{
	class SwitchSceneCommand final : public BaseCommand
	{
	public:

		void Execute() override {
			SceneManager::GetInstance().GoNextScene();
		}

	private:

	};
}

