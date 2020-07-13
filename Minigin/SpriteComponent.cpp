#include "MiniginPCH.h"
#include "Time.h"
#include "SpriteSheetManager.h"
#include "SpriteComponent.h"
#include "RenderComponent.h"

kd::SpriteComponent::SpriteComponent(SpriteInfo& spriteInfo, unsigned int defaultClipId) : m_SpriteInfo(spriteInfo), m_RenderComponent(nullptr)
{
	ChangeSpriteInfo(spriteInfo, defaultClipId);
}

void kd::SpriteComponent::Initialize()
{
	m_RenderComponent = GetGameObject()->GetComponent<RenderComponent>();
	m_RenderComponent->SetTexture(SpriteSheetManager::GetInstance().GetTexture(m_SpriteInfo.SpriteSheetID));
	
	const auto scale = GetGameObject()->GetTransform().GetScale();
	m_ScaleX = static_cast<int>(scale.x);
	m_ScaleY = static_cast<int>(scale.y);

	// Sprite Source Rect
	m_SrcRect.x = m_SpriteInfo.Rect.x;
	m_SrcRect.y = m_SpriteInfo.Rect.y;
	m_SrcRect.w = m_SpriteInfo.Rect.w;
	m_SrcRect.h = m_SpriteInfo.Rect.h;

	// Sprite Desc Rect
	m_DescRect.x = 0;
	m_DescRect.y = 0;
	m_DescRect.w = m_SpriteInfo.Rect.w * m_ScaleX;
	m_DescRect.h = m_SpriteInfo.Rect.h * m_ScaleY;
}

void kd::SpriteComponent::Update()
{
	m_DescRect.w = m_SpriteInfo.Rect.w * m_ScaleX;
	m_DescRect.h = m_SpriteInfo.Rect.h * m_ScaleY;

	m_RenderComponent->SetDestRect(GetDescRect());
	m_RenderComponent->SetSourceRect(GetSourceRect());

	if (m_Pause && m_SpriteInfo.Clips.empty()) return;

	if(m_SpriteInfo.Clips.count(m_ClipID) == false)
		return;

	m_AccuSec += Time::GetInstance().DeltaTime();

	if (m_AccuSec >= m_SpriteInfo.Speed) {

		//Next Frame
		m_CurrentFrame++;
		//Reset Frame ElaspedSec
		m_AccuSec -= m_SpriteInfo.Speed;

		auto clip = m_SpriteInfo.Clips.at(m_ClipID);

		if (m_CurrentFrame > (clip.FrameIndex + clip.FrameCount) - 1)
		{
			if(m_SpriteInfo.Clips.count(m_NextClipID)) 
			{
				m_ClipID = m_NextClipID;
			}
			
			m_CurrentFrame = m_SpriteInfo.Clips.at(m_ClipID).FrameIndex;
		}
	}
}
 
void kd::SpriteComponent::Render() const {}

SDL_Rect& kd::SpriteComponent::GetSourceRect() 
{
	m_SrcRect.y = m_SpriteInfo.Rect.y;
	m_SrcRect.x = m_SpriteInfo.Rect.x + ((m_SrcRect.w + m_SpriteInfo.Offset) * m_CurrentFrame);
	m_SrcRect.w = m_SpriteInfo.Rect.w;
	m_SrcRect.h = m_SpriteInfo.Rect.h;
	return m_SrcRect;
}

SDL_Rect& kd::SpriteComponent::GetDescRect() 
{
	const auto pos = GetGameObject()->GetTransform().GetPosition();
	m_DescRect.x = static_cast<int>(pos.x);
	m_DescRect.y = static_cast<int>(pos.y);
	m_DescRect.w = m_SpriteInfo.Rect.w * m_ScaleX;
	m_DescRect.h = m_SpriteInfo.Rect.h * m_ScaleY;

	return m_DescRect;
}

bool kd::SpriteComponent::SetCurrentClip(unsigned int id)
{
	if(m_SpriteInfo.Clips.count(id))
	{
		m_NextClipID = id;
		return true;
	}

	return false;
}

void kd::SpriteComponent::ChangeSpriteInfo(SpriteInfo & info, int clipID)
{ 
	m_SpriteInfo = info; 
	m_ClipID = clipID; 
	m_NextClipID = clipID;
	m_CurrentFrame = m_SpriteInfo.Clips[clipID].FrameIndex;
};