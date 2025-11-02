#pragma once

struct alignas(16) Vector4
{
	float x;
	float y;
	float z;
	float w;

	inline constexpr Vector4() noexcept :
		x(0.0f), y(0.0f), z(0.0f), w(0.0f)
	{
	}

	inline constexpr Vector4(float x, float y, float z, float w) noexcept :
		x(x), y(y), z(z), w(w)
	{
	}

	inline constexpr float& operator[](size_t index) noexcept
	{
		return static_cast<float*>(&x)[index];
	}

	inline constexpr const float& operator[](size_t index) const noexcept
	{
		return static_cast<const float*>(&x)[index];
	}

	inline constexpr Vector4 operator+(const Vector4& other) const noexcept
	{
		return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
	}

	inline constexpr Vector4 operator-(const Vector4& other) const noexcept
	{
		return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
	}

	inline constexpr Vector4 operator*(const Vector4& other) const noexcept
	{
		return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
	}

	inline constexpr Vector4 operator/(const Vector4& other) const noexcept
	{
		return Vector4(x / other.x, y / other.y, z / other.z, w / other.w);
	}
};