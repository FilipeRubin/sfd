#pragma once

struct Vector3
{
	float x;
	float y;
	float z;

	inline constexpr Vector3() noexcept :
		x(0.0f), y(0.0f), z(0.0f)
	{
	}

	inline constexpr Vector3(float x, float y, float z) noexcept :
		x(x), y(y), z(z)
	{
	}

	inline constexpr Vector3 operator+(const Vector3& other) const noexcept
	{
		return Vector3(x + other.x, y + other.y, z + other.z);
	}

	inline constexpr Vector3 operator-(const Vector3& other) const noexcept
	{
		return Vector3(x - other.x, y - other.y, z - other.z);
	}

	inline constexpr Vector3 operator*(const Vector3& other) const noexcept
	{
		return Vector3(x * other.x, y * other.y, z * other.z);
	}

	inline constexpr Vector3 operator/(const Vector3& other) const noexcept
	{
		return Vector3(x / other.x, y / other.y, z / other.z);
	}
};