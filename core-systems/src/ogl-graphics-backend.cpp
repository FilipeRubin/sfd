#include "ogl-graphics-backend.h"
#include "ogl.h"
#ifdef _WIN32
#include <Windows.h>

unsigned int OGLGraphicsBackend::s_instanceCount = 0U;

OGLGraphicsBackend::OGLGraphicsBackend(const void* windowHandle) :
	m_windowHandle(windowHandle),
	m_oglContext(nullptr)
{
}

bool OGLGraphicsBackend::TryInitialize()
{
	if (not TryIncrement())
	{
		return false;
	}
	
	m_oglContext = CreateContext(m_windowHandle);
	if (m_oglContext == nullptr)
	{
		Finalize();
		return false;
	}

	return true;
}

void OGLGraphicsBackend::MakeCurrent() const
{
	HDC hdc = GetDC((HWND)m_windowHandle);
	wglMakeCurrent(hdc, (HGLRC)m_oglContext);
	ReleaseDC((HWND)m_windowHandle, hdc);
}

void OGLGraphicsBackend::Clear(float r, float g, float b) const
{
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void OGLGraphicsBackend::Finalize()
{
	HDC hdc = GetDC((HWND)m_windowHandle);

	if (wglGetCurrentContext() == m_oglContext)
	{
		wglMakeCurrent(hdc, NULL);
	}

	wglDeleteContext((HGLRC)m_oglContext);

	ReleaseDC((HWND)m_windowHandle, hdc);

	Decrement();
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
