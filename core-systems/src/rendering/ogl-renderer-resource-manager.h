#pragma once
#include <rendering/i-renderer-resource-manager.h>

class OGLRendererResourceManager : public IRendererResourceManager
{
public:
	INDCRenderingRule* CreateNDCRenderingRule() override;
};
