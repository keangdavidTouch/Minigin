#include "pch.h"
#include "DebugComponent.h"
#include "Renderer.h"

kd::DebugComponent::DebugComponent()
{
}

kd::DebugComponent::~DebugComponent()
{
}

void kd::DebugComponent::Initialize()
{
}

void kd::DebugComponent::Update()
{
}

void kd::DebugComponent::Render() const
{
	int x = 16 * 3;
	int y = 16 * 3;

	for (int i = 1; i < 18; i++)
	{
		SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(),0, 255, 0, 0);
		SDL_RenderDrawLine(Renderer::GetInstance().GetSDLRenderer(), 0, y, 672, y);

		y += (16 * 3);
	}

	for (int i = 1; i < 14; i++)
	{
		SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(),0, 255, 0, 0);
		SDL_RenderDrawLine(Renderer::GetInstance().GetSDLRenderer(), x, 0, x, 864);

		x += (16 * 3);
	}
}
