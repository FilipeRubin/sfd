#include "ogl-graphics-backend.h"
#include "ogl.h"
#ifdef _WIN32
#include <Windows.h>
#include <iostream>

// From WGL_ARB_pixel_format
#define WGL_DRAW_TO_WINDOW_ARB 0x2001
#define WGL_SUPPORT_OPENGL_ARB 0x2010
#define WGL_DOUBLE_BUFFER_ARB 0x2011
#define WGL_PIXEL_TYPE_ARB 0x2013
#define WGL_COLOR_BITS_ARB 0x2014
#define WGL_DEPTH_BITS_ARB 0x2022
#define WGL_STENCIL_BITS_ARB 0x2023

#define WGL_TYPE_RGBA_ARB 0x202B
#define WGL_TYPE_COLORINDEX_ARB 0x202C

// From WGL_ARB_create_context
#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#define WGL_CONTEXT_FLAGS_ARB 0x2094
#define WGL_CONTEXT_PROFILE_MASK_ARB 0x9126

#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002

typedef BOOL(*PFNWGLCHOOSEPIXELFORMATARB)(HDC hdc, const int* piAttribIList, const FLOAT* pfAttribFList, UINT nMaxFormats, int* piFormats, UINT* nNumFormats);
PFNWGLCHOOSEPIXELFORMATARB wglChoosePixelFormatARB = nullptr;
typedef HGLRC(*PFNWGLCREATECONTEXTATTRIBSARB)(HDC hdc, HGLRC hshareContext, const int* attribList);
PFNWGLCREATECONTEXTATTRIBSARB wglCreateContextAttribsARB = nullptr;

unsigned int OGLGraphicsBackend::s_instanceCount = 0U;

OGLGraphicsBackend::OGLGraphicsBackend(const void* windowHandle) :
	m_windowHandle(windowHandle),
	m_oglContext(nullptr)
{
}

bool OGLGraphicsBackend::TryInitialize()
{
	// CHANGE THIS LATER FOR A BETTER LOGIC
	if (wglChoosePixelFormatARB == nullptr)
	{
		LoadFunctions();
		if (wglChoosePixelFormatARB == nullptr)
		{
			return false;
		}
	}

	HDC hdc = GetDC((HWND)m_windowHandle);

	const int pixelFormatAttribs[] = {
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
		WGL_COLOR_BITS_ARB, 32,
		WGL_DEPTH_BITS_ARB, 24,
		WGL_STENCIL_BITS_ARB, 8,
		0
	};
	
	int pixelFormat = 0;
	UINT formatsCount = 0U;
	
	if (wglChoosePixelFormatARB(hdc, pixelFormatAttribs, NULL, 1U, &pixelFormat, &formatsCount) == FALSE)
	{
		ReleaseDC((HWND)m_windowHandle, hdc);
		return false;
	}
	
	if (formatsCount == 0U)
	{
		ReleaseDC((HWND)m_windowHandle, hdc);
		return false;
	}

	PIXELFORMATDESCRIPTOR pfd = {};
	DescribePixelFormat(hdc, pixelFormat, sizeof(pfd), &pfd);
	if (not SetPixelFormat(hdc, pixelFormat, &pfd))
	{
		ReleaseDC((HWND)m_windowHandle, hdc);
		return false;
	}

	const int contextAttribs[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 6,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};
	HGLRC hglrc = wglCreateContextAttribsARB(hdc, NULL, contextAttribs);

	if (hglrc == NULL)
	{
		DWORD err = GetLastError();
		ReleaseDC((HWND)m_windowHandle, hdc);
		return false;
	}

	wglMakeCurrent(hdc, hglrc);
	m_oglContext = hglrc;
	ReleaseDC((HWND)m_windowHandle, hdc);

	if (not TryIncrement())
	{
		Finalize();
		return false;
	}

	static bool showedDriverStrings = false;

	if (not showedDriverStrings)
	{
		showedDriverStrings = true;
		const unsigned char* glVendor = glGetString(GL_VENDOR);
		const unsigned char* glRenderer = glGetString(GL_RENDERER);
		const unsigned char* glVersion = glGetString(GL_VERSION);
		std::cout << "GL_VENDOR: " << glVendor << std::endl;
		std::cout << "GL_RENDERER: " << glRenderer << std::endl;
		std::cout << "GL_VERSION: " << glVersion << std::endl;
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
	Decrement();

	HDC hdc = GetDC((HWND)m_windowHandle);

	if (wglGetCurrentContext() == m_oglContext)
	{
		wglMakeCurrent(hdc, NULL);
	}

	wglDeleteContext((HGLRC)m_oglContext);

	ReleaseDC((HWND)m_windowHandle, hdc);
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

void OGLGraphicsBackend::LoadFunctions()
{
	HINSTANCE hInstance = GetModuleHandle(NULL);
	const wchar_t* className = L"FakeContextWC";
	WNDCLASS wc = {};
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = DefWindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = className;
	if (RegisterClass(&wc) == NULL)
	{
		return;
	}

	HWND hwnd = CreateWindow(
		className,
		L"Dummy window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL,
		hInstance,
		NULL
	);

	if (hwnd == NULL)
	{
		UnregisterClass(className, hInstance);
		return;
	}

	HDC hdc = GetDC(hwnd);

	PIXELFORMATDESCRIPTOR pfd = {};
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1U;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;
	
	int pixelFormat = ChoosePixelFormat(hdc, &pfd);
	if (pixelFormat == 0)
	{
		ReleaseDC(hwnd, hdc);
		DestroyWindow(hwnd);
		UnregisterClass(className, hInstance);
		return;
	}

	if (not SetPixelFormat(hdc, pixelFormat, &pfd))
	{
		ReleaseDC(hwnd, hdc);
		DestroyWindow(hwnd);
		UnregisterClass(className, hInstance);
		return;
	}

	HGLRC hglrc = wglCreateContext(hdc);
	if (hglrc == NULL)
	{
		ReleaseDC(hwnd, hdc);
		DestroyWindow(hwnd);
		UnregisterClass(className, hInstance);
		return;
	}

	wglMakeCurrent(hdc, hglrc);

	wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARB)wglGetProcAddress("wglChoosePixelFormatARB");
	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARB)wglGetProcAddress("wglCreateContextAttribsARB");

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hglrc);
	ReleaseDC(hwnd, hdc);
	DestroyWindow(hwnd);
	UnregisterClass(className, hInstance);
}

#endif // _WIN32
