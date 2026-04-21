#pragma once

struct Dimensions
{
	int x = 0;
	int y = 0;

	inline Dimensions() noexcept :
		x(0), y(0)
	{
	}

	inline Dimensions(int x, int y) noexcept :
		x(x), y(y)
	{
	}
};