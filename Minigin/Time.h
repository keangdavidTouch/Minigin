//#pragma once
//class Time
//{
//public:
//	static Time& getInstance();
//	~Time();
//	float DeltaTime() const;
//	void SetDeltaTime(float deltaTime);
//
//private:
//	Time();
//	static Time* m_Instance;
//	float m_DeltaTime;
//};
//
#pragma once
#include "Singleton.h"

namespace kd
{
	class Time : public kd::Singleton<Time>
	{

	friend class MiniginGame;

	public:
		Time() = default;
		float DeltaTime() const;

	private:
		static Time* m_Instance;
		float m_DeltaTime;
	};
}


