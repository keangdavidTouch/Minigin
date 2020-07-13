#include "MiniginPCH.h"
#include "AIComponent.h"
#include "Time.h"
#include "PathFinder.h"

kd::AIComponent::AIComponent(GameObject * target, float gridSize, bool enable)
	: m_Target(target)
	, m_Enable(enable)
	, m_GridSize(gridSize)
{
};

void kd::AIComponent::Initialize(){}

void kd::AIComponent::Update()
{
	if(m_Enable == false) 
		return;

	if(CalculatePath() == false) 
		return; 

	auto pathPos = m_Paths.back();
	auto playerPos = GetGameObject()->GetTransform().GetPosition();

	//After Switching from GhostState
	if(m_ExitGhostMode)
	{
		playerPos.x = pathPos.x;
		playerPos.y = pathPos.y;
		GetGameObject()->GetTransform().SetPosition(playerPos);
		m_ExitGhostMode = false;
		return;
	}
	
	//Caculate Player Position
	glm::vec3 dir{};
	if(pathPos.x > playerPos.x)
		dir.x = 1;
	else if (pathPos.x < playerPos.x)
		dir.x = -1;
	else if(pathPos.y > playerPos.y)
		dir.y = 1;
	else if (pathPos.y < playerPos.y)
		dir.y = -1;

	playerPos += (dir * m_Speed);

	if(dir.y == 0)
		playerPos.y = glm::round(playerPos.y / m_GridSize) * m_GridSize;
	else if (dir.x == 0)
		playerPos.x = glm::round(playerPos.x / m_GridSize) * m_GridSize;

	//Update Position & Rotation
	auto& transform = GetGameObject()->GetTransform();
	transform.SetPosition(playerPos);

	if (transform.GetPosition().x < pathPos.x) {
		transform.SetFlip(Transform::Flip::None);
		transform.SetRotation(0);
	}
	else {
		transform.SetFlip(Transform::Flip::Vertical);
		transform.SetRotation(180);
	}
}

void kd::AIComponent::Render() const 
{ 
	PathFinder::GetInstance().DebugRenderPath();
}

bool kd::AIComponent::NoAvailablePath()
{
	if(m_Enable == false)
		CalculatePath();

	return m_NoAvailablePath;
}

bool kd::AIComponent::CalculatePath()
{
	auto playerPos = GetGameObject()->GetTransform().GetPosition();
	auto targetPos = m_Target->GetTransform().GetPosition();
	auto fromCol = static_cast<unsigned short>(glm::round(playerPos.x / m_GridSize));
	auto fromRow = static_cast<unsigned short>(glm::round(playerPos.y / m_GridSize));
	auto toCol = static_cast<unsigned short>(glm::round(targetPos.x / m_GridSize));
	auto toRow = static_cast<unsigned short>(glm::round(targetPos.y / m_GridSize));

	m_Paths.clear();
	m_Paths = PathFinder::GetInstance().FindPath(fromCol, fromRow, toCol, toRow);
	PathFinder::GetInstance().ResetNodes();

	m_NoAvailablePath = m_Paths.empty(); 

	return !m_NoAvailablePath;
}
