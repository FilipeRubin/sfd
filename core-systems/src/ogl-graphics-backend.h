#pragma once
#include <i-graphics-backend.h>

class OGLGraphicsBackend : public IGraphicsBackend
{
public:
	OGLGraphicsBackend(const void* windowHandle);
	bool TryInitialize() override;
	void MakeCurrent() const override;
	void Clear(float r, float g, float b) const override;
	void Finalize() override;
private:
	static unsigned int s_instanceCount;
	static bool TryIncrement();
	static void Decrement();
	const void* m_windowHandle;
	const void* m_oglContext;
};