#pragma once

struct Color8
{
	union
	{
		struct
		{
			unsigned char r;
			unsigned char g;
			unsigned char b;
			unsigned char a;
		};
		unsigned int value;
	};

	inline constexpr Color8() noexcept :
		r(0U), g(0U), b(0U), a(0U)
	{
	}

	inline constexpr Color8(unsigned char r, unsigned char g, unsigned char b, unsigned char a) noexcept :
		r(r), g(g), b(b), a(a)
	{
	}

	inline constexpr Color8(unsigned char r, unsigned char g, unsigned char b) noexcept :
		r(r), g(g), b(b), a(255U)
	{
	}

	inline constexpr Color8(unsigned int value) noexcept :
		value(value)
	{
	}

	inline constexpr explicit operator unsigned int() const noexcept
	{
		return value;
	}
};