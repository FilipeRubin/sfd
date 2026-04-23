#pragma once

class IRendererResource
{
public:
	virtual ~IRendererResource() = default;
	virtual bool IsValid() const = 0;
};
