#include "ogl-graphics-backend.h"
#include "ogl.h"
#include "rendering/ogl-renderer.h"
#include "rendering/ogl-renderer-resource-manager.h"
#ifdef _WIN32
#include <Windows.h>

unsigned int OGLGraphicsBackend::s_instanceCount = 0U;
OGLGraphicsBackend* OGLGraphicsBackend::s_current = nullptr;

OGLGraphicsBackend* OGLGraphicsBackend::GetCurrent()
{
	return s_current;
}

OGLGraphicsBackend::OGLGraphicsBackend(const void* windowHandle) :
	m_windowHandle(windowHandle),
	m_oglContext(nullptr),
	m_hdc(nullptr),
	m_renderer(nullptr)
{
}

bool OGLGraphicsBackend::TryInitialize(IGraphicsBackend* sharedBackend)
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

	HGLRC sharedContext = nullptr;
	if (sharedBackend)
	{
		sharedContext = (HGLRC)dynamic_cast<OGLGraphicsBackend*>(sharedBackend)->m_oglContext;
	}

	m_oglContext = CreateContext(m_windowHandle, sharedContext);
	if (m_oglContext == nullptr)
	{
		Finalize();
		return false;
	}

	m_renderer = new OGLRenderer(this);

	return true;
}

void OGLGraphicsBackend::MakeCurrent() const
{
	wglMakeCurrent((HDC)m_hdc, (HGLRC)m_oglContext);
	s_current = const_cast<OGLGraphicsBackend*>(this);
	OGLRendererResourceManager* rm = dynamic_cast<OGLRendererResourceManager*>(GetRenderer()->GetResourceManager());
	rm->Update();
}

void OGLGraphicsBackend::SwapBuffers() const
{
	::SwapBuffers((HDC)m_hdc);
}

void OGLGraphicsBackend::Finalize()
{
	delete m_renderer;

	if (wglGetCurrentContext() == m_oglContext)
	{
		wglMakeCurrent((HDC)m_hdc, NULL);
	}

	wglDeleteContext((HGLRC)m_oglContext);

	ReleaseDC((HWND)m_windowHandle, (HDC)m_hdc);

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
