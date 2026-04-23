#pragma once
#include "i-renderer-resource.h"
#include <rendering/i-drawable.h>

class IMesh3D : public IRendererResource, public IDrawable
{
public:
	virtual ~IMesh3D() = default;
};
