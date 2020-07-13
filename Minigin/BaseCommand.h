#pragma once

namespace kd
{
	struct InputAction;

	class BaseCommand 
	{
	public:
		BaseCommand() = default;
		~BaseCommand() = default;
		virtual void Execute() = 0;
	protected:
	};


}



