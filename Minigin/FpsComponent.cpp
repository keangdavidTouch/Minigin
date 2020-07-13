#include "MiniginPCH.h"
#include "Time.h"
#include "FpsComponent.h"
#include "TextComponent.h"

kd::FpsComponent::FpsComponent()
	: m_TextComponent(nullptr)
{
}

kd::FpsComponent::~FpsComponent()
{
}

void kd::FpsComponent::Initialize()
{
	m_TextComponent = GetGameObject()->GetComponent<TextComponent>();
	m_TextComponent->SetTextColor({255, 255, 0, 255});
}

void kd::FpsComponent::Update()
{
	m_TextComponent->SetText(std::to_string(int(1 / Time::GetInstance().DeltaTime())) + " FPS");
}

void kd::FpsComponent::Render() const 
{
	
}
