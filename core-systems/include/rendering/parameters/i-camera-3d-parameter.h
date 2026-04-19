#pragma once
#include "i-render-parameter.h"
#include <types/camera-3d.h>

class ICamera3DParameter : public IRenderParameter
{
public:
	virtual ~ICamera3DParameter() = default;
	virtual Camera3D& Camera() = 0;
};