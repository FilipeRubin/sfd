#pragma once

struct Dimensions
{
	int width = 0;
	int height = 0;

	inline Dimensions() noexcept :
		width(0), height(0)
	{
	}

	inline Dimensions(int x, int y) noexcept :
		width(x), height(y)
	{
	}
};
