#pragma once
#include "i-lambert-rendering-rule.h"
#include "i-mesh-3d.h"
#include "i-texture-2d.h"
#include <types/vertex-3d.h>
#include <types/color8.h>

class IRendererResourceManager
{
public:
	virtual ~IRendererResourceManager() = default;
	virtual ILambertRenderingRule* CreateLambertRenderingRule() = 0;
	virtual IMesh3D* Create3DMesh(Vertex3D* vertices, size_t verticesLength, unsigned int* indices, size_t indicesLength) = 0;
	virtual ITexture2D* CreateTexture2D(Color8* data, size_t dataLength, const Dimensions& size) = 0;
};
