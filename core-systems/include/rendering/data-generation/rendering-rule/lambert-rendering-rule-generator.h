#pragma once
#include "i-rendering-rule-generator.h"

class LambertRenderingRuleGenerator : public IRenderingRuleGenerator
{
public:
	Type GetType() const override;
};
