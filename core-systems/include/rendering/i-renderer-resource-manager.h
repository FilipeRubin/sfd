#pragma once
#include "i-ndc-rendering-rule.h"
#include "i-ndc-shape.h"
#include "i-basic-3d-rendering-rule.h"
#include "i-basic-3d-mesh.h"

class IRendererResourceManager
{
public:
	virtual ~IRendererResourceManager() = default;
	virtual INDCRenderingRule* CreateNDCRenderingRule() = 0;
	virtual IBasic3DRenderingRule* CreateBasic3DRenderingRule() = 0;
	virtual INDCShape* CreateNDCShape(float* vertices, size_t length) = 0;
	virtual IBasic3DMesh* CreateBasic3DMesh(float* vertices, size_t verticesLength, unsigned int* indices, size_t indicesLength) = 0;
};