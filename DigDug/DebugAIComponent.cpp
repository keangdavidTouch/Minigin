#include "pch.h"
#include "DebugAIComponent.h"
#include "PathFinder.h"
#include "Renderer.h"

void kd::DebugAIComponent::Initialize()
{
}

void kd::DebugAIComponent::Update()
{
	SDL_Rect rect = {0, 0, DRAWIZE, DRAWIZE};

	int x, y;
	if (SDL_MOUSEBUTTONDOWN && SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		m_ClickStart = true;
		rect.x = (x / SIZE) * SIZE;
		rect.y = (y / SIZE) *SIZE;
		m_StartNode = rect;

		auto pos = m_FindObject->GetTransform().GetPosition();
		m_Paths = PathFinder::GetInstance().FindPath(short(x / SIZE), short(y / SIZE), short(pos.x / SIZE), short(pos.y / SIZE));//, 13, 15);
		PathFinder::GetInstance().ResetNodes();
	}
}

void kd::DebugAIComponent::Render() const
{
	SDL_Rect rect = {0, 0, DRAWIZE, DRAWIZE};

	PathFinder::GetInstance().DebugRenderCellGrids();

	SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(),255, 0, 0, 0);
	SDL_RenderFillRect(Renderer::GetInstance().GetSDLRenderer(), &m_StartNode);

	for (auto path : m_Paths)
	{
		SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(),0, 0, 255, 0);
		SDL_Rect r = {int(path.x) , int(path.y) , DRAWIZE, DRAWIZE};
		SDL_RenderFillRect(Renderer::GetInstance().GetSDLRenderer(), &r);
	}
	
	SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(),255, 255, 0, 0);
	SDL_RenderDrawRect(Renderer::GetInstance().GetSDLRenderer(), &rect);
}
