#pragma once
#include "data-generation/i-mesh-3d-generator.h"
#include "resources/i-rendering-rule.h"
#include "resources/i-mesh-3d.h"
#include "resources/i-texture-2d.h"
#include <types/color8.h>

class IRendererResourceManager
{
public:
	virtual ~IRendererResourceManager() = default;
	virtual IRenderingRule* CreateLambertRenderingRule() = 0;
	virtual IRenderingRule* CreateUnshadedRenderingRule() = 0;
	virtual IMesh3D* Create3DMesh(const IMesh3DGenerator& generator) = 0;
	virtual ITexture2D* CreateTexture2D(Color8* data, size_t dataLength, const Dimensions& size) = 0;
};
