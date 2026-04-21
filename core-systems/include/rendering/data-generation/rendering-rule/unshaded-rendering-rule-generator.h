#pragma once
#include "i-rendering-rule-generator.h"

class UnshadedRenderingRuleGenerator : public IRenderingRuleGenerator
{
public:
	Type GetType() const;
};
