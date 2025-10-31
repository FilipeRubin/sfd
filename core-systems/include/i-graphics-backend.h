#pragma once
#include "rendering/i-renderer.h"

class IGraphicsBackend
{
public:
	virtual ~IGraphicsBackend() = default;
	virtual bool TryInitialize() = 0;
	virtual void MakeCurrent() const = 0;
	virtual void SwapBuffers() const = 0;
	virtual void Finalize() = 0;
	virtual IRenderer* GetRenderer() const = 0;
};
