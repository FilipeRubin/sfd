#pragma once

class IBindable
{
public:
	virtual ~IBindable() = default;
	virtual void Bind() const = 0;
};
