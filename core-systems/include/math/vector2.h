#pragma once

struct Vector2
{
	float x;
	float y;

	inline constexpr Vector2(float x, float y) noexcept :
		x(x), y(x)
	{
	}

	inline constexpr Vector2 operator+(const Vector2& other) const noexcept
	{
		return Vector2(x + other.x, y + other.y);
	}

	inline constexpr Vector2 operator-(const Vector2& other) const noexcept
	{
		return Vector2(x - other.x, y - other.y);
	}

	inline constexpr Vector2 operator*(const Vector2& other) const noexcept
	{
		return Vector2(x * other.x, y * other.y);
	}

	inline constexpr Vector2 operator/(const Vector2& other) const noexcept
	{
		return Vector2(x / other.x, y / other.y);
	}
};