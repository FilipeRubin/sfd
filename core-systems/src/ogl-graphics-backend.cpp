#include "ogl-graphics-backend.h"
#ifdef _WIN32
#include <Windows.h>
#include <gl/GL.h>

OGLGraphicsBackend::OGLGraphicsBackend(const void* windowHandle) :
	m_windowHandle(windowHandle),
	m_oglContext(nullptr)
{
}

bool OGLGraphicsBackend::TryInitialize()
{
	PIXELFORMATDESCRIPTOR pfd = {
		.nSize = sizeof(PIXELFORMATDESCRIPTOR),
		.nVersion = 1,
		.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		.iPixelType = PFD_TYPE_RGBA,
		.cColorBits = 32,
		.cRedBits = 0,
		.cRedShift = 0,
		.cGreenBits = 0,
		.cGreenShift = 0,
		.cBlueBits = 0,
		.cBlueShift = 0,
		.cAlphaBits = 0,
		.cAlphaShift = 0,
		.cAccumBits = 0,
		.cAccumRedBits = 0,
		.cAccumGreenBits = 0,
		.cAccumBlueBits = 0,
		.cAccumAlphaBits = 0,
		.cDepthBits = 24,
		.cStencilBits = 8,
		.cAuxBuffers = 0,
		.iLayerType = PFD_MAIN_PLANE,
		.bReserved = 0,
		.dwLayerMask = 0,
		.dwVisibleMask = 0,
		.dwDamageMask = 0
	};
	
	HDC hdc = GetDC((HWND)m_windowHandle);

	int pixelFormat = ChoosePixelFormat(hdc, &pfd);

	if (pixelFormat == 0)
	{
		ReleaseDC((HWND)m_windowHandle, hdc);
		return false;
	}

	if (SetPixelFormat(hdc, pixelFormat, &pfd) == FALSE)
	{
		ReleaseDC((HWND)m_windowHandle, hdc);
		return false;
	}

	HGLRC hglrc = wglCreateContext(hdc);
	wglMakeCurrent(hdc, hglrc);
	m_oglContext = hglrc;
	ReleaseDC((HWND)m_windowHandle, hdc);

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
}
#endif // _WIN32
