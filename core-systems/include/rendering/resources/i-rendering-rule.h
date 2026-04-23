#pragma once
#include "i-renderer-resource.h"

class IRenderingRule : public IRendererResource
{
public:
	virtual ~IRenderingRule() = default;
	virtual void Bind() = 0;
};
