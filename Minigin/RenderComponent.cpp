#include "MiniginPCH.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "RenderComponent.h"
#include "SpriteComponent.h"

kd::RenderComponent::RenderComponent() : m_Texture(nullptr), m_SrcRect() , m_DescRect()
{
}

kd::RenderComponent::RenderComponent(std::shared_ptr<Texture2D> texture, SDL_Rect& srcDest)
	: m_Texture { texture }
	, m_SrcRect(srcDest)
	, m_DescRect()
{
}

kd::RenderComponent::RenderComponent(const std::string& filename, SDL_Rect& srcDest)
	: m_Texture { ResourceManager::GetInstance().LoadTexture(filename) }
	, m_SrcRect(srcDest)
	, m_DescRect()
{
}

kd::RenderComponent::~RenderComponent(){}
 
void kd::RenderComponent::Initialize(){}

void kd::RenderComponent::Update() {

	if (!m_Texture) return;

	const auto transform = GetGameObject()->GetTransform();
	const auto pos = transform.GetPosition();
	const auto scale = transform.GetScale();

	m_DescRect.x = static_cast<int>(pos.x);
	m_DescRect.y = static_cast<int>(pos.y);
	m_DescRect.w = static_cast<int>(m_SrcRect.w * scale.x);
	m_DescRect.h = static_cast<int>(m_SrcRect.h * scale.y);
}
      
void kd::RenderComponent::Render() const
{
	if (!m_Texture) return;

	const auto transform = GetGameObject()->GetTransform();
	
	if (!SDL_RectEmpty(&m_SrcRect) && !SDL_RectEmpty(&m_DescRect)) {
		Renderer::GetInstance().RenderTexture(*m_Texture, &m_DescRect, &m_SrcRect, static_cast<SDL_RendererFlip>(transform.GetFlip()), transform.GetRotation());
	}
	else {
		const auto pos = transform.GetPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

void kd::RenderComponent::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_Texture = texture;
}
