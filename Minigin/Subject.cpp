#include "MiniginPCH.h"
#include "Subject.h"
#include <algorithm>
#include "Observer.h"

kd::Subject::~Subject()
{
	for (auto observer : m_Observers) {
		delete observer;
	}
}

void kd::Subject::AddObserver(Observer * observer)
{
	m_Observers.push_back(observer);
}

void kd::Subject::RemoveObserver(Observer * observer)
{
	for (size_t i = 0; i < m_Observers.size(); ++i) {

		if (m_Observers[i] == observer) {
			m_Observers.erase(std::remove(m_Observers.begin(), m_Observers.end(), observer));
		}
	}
}

void kd::Subject::Notify(int eventType, GameObject* object)
{
	for (auto observer : m_Observers) {
		observer->OnNotify(eventType, object);
	}
}
