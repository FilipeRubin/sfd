#pragma once

class IRenderingRule
{
public:
	virtual ~IRenderingRule() = default;
	virtual void Bind() const = 0;
};