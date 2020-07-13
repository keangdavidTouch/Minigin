#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#pragma warning(pop)

namespace kd
{
	class Transform final
	{
	public:
		enum class Flip
		{
			None = 0, Horizontal = 1, Vertical = 2, Both = (1 | 2)
		};

		//----------World-Space--------------
		const glm::vec3& GetPosition() const { return m_Position; }
		const glm::vec2& GetScale() const { return m_Scale; }
		const float GetRotation() const { return m_Rotation; };

		void SetPosition(float x, float y, float z = 1.f);
		void SetPosition(glm::vec3& position);
		void SetScale(float x, float y);
		void SetScale(float scale);
		void SetRotation(float rot) { m_Rotation = rot; };

		// Flip For 2D-Sprite
		Flip GetFlip() const { return m_Flip; };
		void SetFlip(Flip type) { m_Flip = type; };

		//----------Local-Space--------------
		const glm::vec3& GetLocalPosition() const { return m_LocalPos; }
		const glm::vec2& GetLocalScale() const { return m_LocalScale; }
		const float GetLocalRotation() const { return m_LocalRot; };

		void SetLocalPosition(float x, float y, float z = 1.f);
		void SetLocalPosition(glm::vec3& position) { m_LocalPos = position; }
		void SetLocalScale(float x, float y) { m_LocalScale.x = x; m_LocalScale.y = y; };
		void SetLocalRotation(float rot) { m_LocalRot = rot; };

	private:
		float m_Rotation{0.f};
		glm::vec3 m_Position{0,0,0};
		glm::vec2 m_Scale{1,1};

		// Local Space Transform
		float m_LocalRot{0.f};
		glm::vec3 m_LocalPos{0,0,0};
		glm::vec2 m_LocalScale{1,1};

		Flip m_Flip = Flip::None;
	};
}
