#pragma once
#include <i-graphics-backend.h>

class OGLGraphicsBackend : public IGraphicsBackend
{
public:
	OGLGraphicsBackend(const void* windowHandle);
	bool TryInitialize() override;
	void MakeCurrent() const override;
	void SwapBuffers() const override;
	void Finalize() override;
	IRenderer* GetRenderer() const override;
private:
	static unsigned int s_instanceCount;
	static bool TryIncrement();
	static void Decrement();
	const void* m_windowHandle;
	const void* m_oglContext;
	void* m_hdc;
	IRenderer* m_renderer;
};