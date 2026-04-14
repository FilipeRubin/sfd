#pragma once
#include <math/vector2.h>

class ITexture2D
{
public:
	virtual ~ITexture2D() = default;
	virtual Vector2 GetSize() = 0;
};