#pragma once

class IRendererManaged
{
public:
	virtual ~IRendererManaged() = default;
	virtual void Create() = 0;
	virtual void Destroy() = 0;
};