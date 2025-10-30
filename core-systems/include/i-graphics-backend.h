#pragma once

class IGraphicsBackend
{
public:
	virtual ~IGraphicsBackend() = default;
	virtual bool TryInitialize() = 0;
	virtual void MakeCurrent() const = 0;
	virtual void SwapBuffers() const = 0;
	virtual void Clear(float r, float g, float b) const = 0;
	virtual void Finalize() = 0;
};