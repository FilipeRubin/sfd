#pragma once
#include "i-render-parameter.h"
#include <types/directional-light.h>

class IDirectionalLightParameter : public IRenderParameter
{
public:
	virtual ~IDirectionalLightParameter() = default;
	virtual DirectionalLight& Light() = 0;
};