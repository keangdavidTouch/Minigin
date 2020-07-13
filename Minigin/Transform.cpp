#include "MiniginPCH.h"
#include "Transform.h"

void kd::Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void kd::Transform::SetPosition(glm::vec3& position)
{
	m_Position = position;
}

void kd::Transform::SetScale(float x, float y)
{
	m_Scale.x = x;
	m_Scale.y = y;
}

void kd::Transform::SetScale(float scale)
{
	m_Scale.x = scale;
	m_Scale.y = scale;
}

void kd::Transform::SetLocalPosition(float x, float y, float z)
{
	m_LocalPos.x = x;
	m_LocalPos.y = y;
	m_LocalPos.z = z;
}
