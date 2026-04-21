#pragma once

class IRenderingRuleGenerator
{
public:
	enum class Type
	{
		UNSHADED,
		LAMBERT,
		CUSTOM
	};
	virtual ~IRenderingRuleGenerator() = default;
	virtual Type GetType() const = 0;
	virtual const void* GetCustomData() const { return nullptr; }
};
