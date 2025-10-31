#include "ogl-graphics-backend.h"
#include "ogl.h"
#include "rendering/ogl-renderer.h"
#ifdef _WIN32
#include <Windows.h>

unsigned int OGLGraphicsBackend::s_instanceCount = 0U;

OGLGraphicsBackend::OGLGraphicsBackend(const void* windowHandle) :
	m_windowHandle(windowHandle),
	m_oglContext(nullptr),
	m_hdc(nullptr),
	m_renderer(nullptr)
{
}

bool OGLGraphicsBackend::TryInitialize()
{
	if (m_oglContext != nullptr)
	{
		return true;
	}

	if (not TryIncrement())
	{
		return false;
	}
	
	m_hdc = GetDC((HWND)m_windowHandle);

	m_oglContext = CreateContext(m_windowHandle);
	if (m_oglContext == nullptr)
	{
		Finalize();
		return false;
	}

	m_renderer = new OGLRenderer();

	return true;
}

void OGLGraphicsBackend::MakeCurrent() const
{
	wglMakeCurrent((HDC)m_hdc, (HGLRC)m_oglContext);
}

void OGLGraphicsBackend::SwapBuffers() const
{
	::SwapBuffers((HDC)m_hdc);
}

void OGLGraphicsBackend::Finalize()
{
	if (wglGetCurrentContext() == m_oglContext)
	{
		wglMakeCurrent((HDC)m_hdc, NULL);
	}

	wglDeleteContext((HGLRC)m_oglContext);

	ReleaseDC((HWND)m_windowHandle, (HDC)m_hdc);

	delete m_renderer;

	Decrement();
}

IRenderer* OGLGraphicsBackend::GetRenderer() const
{
	return m_renderer;
}

bool OGLGraphicsBackend::TryIncrement()
{
	if (s_instanceCount == 0U)
	{
		if (not TryLoadOGL())
		{
			return false;
		}
	}
	s_instanceCount++;
	return true;
}

void OGLGraphicsBackend::Decrement()
{
	s_instanceCount--;
	if (s_instanceCount == 0U)
	{
		UnloadOGL();
	}
}

#endif // _WIN32
