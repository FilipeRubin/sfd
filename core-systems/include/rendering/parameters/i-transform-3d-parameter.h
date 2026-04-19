#pragma once
#include <types/transform-3d.h>
#include "i-render-parameter.h"

class ITransform3DParameter : public IRenderParameter
{
public:
	virtual ~ITransform3DParameter() = default;
	virtual Transform3D& Transform() = 0;
};
