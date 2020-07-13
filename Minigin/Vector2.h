#pragma once
struct Vector2 final
{
	float x = 0;
	float y = 0;

	Vector2(float x = 0.f, float y = 0.f) : x(x), y(y) {};
	~Vector2() = default;

	inline auto operator-(const Vector2& v) const
	{
		return Vector2(x - v.x, y - v.y);
	}

	inline auto operator+(const Vector2& v) const
	{
		return Vector2(x + v.x, y + v.y);
	}

	inline auto operator*(const Vector2& v) const
	{
		return Vector2(x * v.x, y * v.y);
	}

	inline auto operator/(const Vector2& v) const
	{
		return Vector2(x / v.x, y / v.y);
	}
};

