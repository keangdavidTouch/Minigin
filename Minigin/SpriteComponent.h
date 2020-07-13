#pragma once
#include "BaseComponent.h"
#include <SDL.h>
#include <unordered_map>

namespace kd {

	struct SpriteClip
	{
		SpriteClip() {};
		SpriteClip(unsigned int frameIndex, unsigned int frameCount) : FrameIndex(frameIndex), FrameCount(frameCount) {};
		unsigned int FrameIndex;
		unsigned int FrameCount;
	};

	struct SpriteInfo
	{
		SpriteInfo(){};
		SpriteInfo(int offset, SDL_Rect&& rect, unsigned int id, unsigned int frameIndex = 0, float speed = 0.1f) 
			: Offset(offset), Rect(rect), StartFrameIndex(frameIndex), SpriteSheetID(id), Speed(speed), Clips() {};

		int Offset = 0;
		SDL_Rect Rect = {};
		unsigned int StartFrameIndex = 0; 
		unsigned int SpriteSheetID = 0;
		float Speed = 0.1f;
		std::unordered_map<int, SpriteClip> Clips = {};
	};

	class RenderComponent;

	class SpriteComponent final : public BaseComponent
	{
	public:
		SpriteComponent(SpriteInfo& spriteInfo, unsigned int defaultClipId);
		~SpriteComponent() = default;

		void Initialize() override;
		void Update() override;
		void Render() const  override;
		
		void SetPosition(glm::vec2 pos) { m_Position = pos; }
		bool SetCurrentClip(unsigned int id); 
		void ChangeSpriteInfo(SpriteInfo& info, int clipID);
		SpriteInfo& GetSpriteInfo() { return m_SpriteInfo; };
		void SetPause(bool p) { m_Pause = p; }
		bool GetPause() const { return m_Pause; };

	private:
		bool m_Pause = false;
		int m_ScaleX, m_ScaleY = 1;
		int m_NextClipID = -1;
		unsigned int m_ClipID = 0;
		unsigned int m_CurrentFrame = 0;
		unsigned int m_SpriteNumberOfCols;
		float m_FrameSec = 0.1f;
		float m_AccuSec = 0.f;
		SpriteInfo m_SpriteInfo;
		RenderComponent* m_RenderComponent;
		glm::vec2 m_Position{0,0};
		SDL_Rect m_SrcRect = SDL_Rect();
		SDL_Rect m_DescRect = SDL_Rect();

		SDL_Rect& GetSourceRect();
		SDL_Rect& GetDescRect();
	};
}
