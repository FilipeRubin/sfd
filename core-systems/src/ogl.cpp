#include "ogl.h"
#include <Windows.h>

static HMODULE s_glLib = NULL;

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
static PFNWGLCHOOSEPIXELFORMATARB wglChoosePixelFormatARB = nullptr;
typedef HGLRC(*PFNWGLCREATECONTEXTATTRIBSARB)(HDC hdc, HGLRC hshareContext, const int* attribList);
static PFNWGLCREATECONTEXTATTRIBSARB wglCreateContextAttribsARB = nullptr;

typedef void (*PFNGLCLEARPROC)(GLbitfield mask);
typedef void (*PFNGLCLEARCOLORPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef const GLubyte*(*PFNGLGETSTRINGPROC)(GLenum name);

void (*glClear)(GLbitfield mask);
void (*glClearColor)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
const GLubyte* (*glGetString)(GLenum name);

static bool TryLoadExtFunctions();

bool TryLoadOGL()
{
	if (not TryLoadExtFunctions())
	{
		return false;
	}

	if (s_glLib != NULL)
		return true;

	s_glLib = LoadLibrary(L"opengl32.dll");

	if (s_glLib == NULL)
		return false;

	glClear = (PFNGLCLEARPROC)GetProcAddress(s_glLib, "glClear");
	glClearColor = (PFNGLCLEARCOLORPROC)GetProcAddress(s_glLib, "glClearColor");
	glGetString = (PFNGLGETSTRINGPROC)GetProcAddress(s_glLib, "glGetString");

	return true;
}

const void* CreateContext(const void* windowHandle)
{
	HDC hdc = GetDC((HWND)windowHandle);

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
		ReleaseDC((HWND)windowHandle, hdc);
		return nullptr;
	}

	if (formatsCount == 0U)
	{
		ReleaseDC((HWND)windowHandle, hdc);
		return nullptr;
	}

	PIXELFORMATDESCRIPTOR pfd = {};
	DescribePixelFormat(hdc, pixelFormat, sizeof(pfd), &pfd);
	if (not SetPixelFormat(hdc, pixelFormat, &pfd))
	{
		ReleaseDC((HWND)windowHandle, hdc);
		return nullptr;
	}

	const int contextAttribs[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 6,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};
	HGLRC hglrc = wglCreateContextAttribsARB(hdc, NULL, contextAttribs);

	ReleaseDC((HWND)windowHandle, hdc);
	return hglrc;
}

void UnloadOGL()
{
	if (s_glLib != NULL)
	{
		FreeLibrary(s_glLib);
		s_glLib = NULL;
	}
}

static bool TryLoadExtFunctions()
{
	if (wglChoosePixelFormatARB != nullptr)
	{
		return true;
	}

	HINSTANCE hInstance = GetModuleHandle(NULL);
	const wchar_t* className = L"FakeContextWC";
	WNDCLASS wc = {};
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = DefWindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = className;
	if (RegisterClass(&wc) == NULL)
	{
		return false;
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
		return false;
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
		return false;
	}

	if (not SetPixelFormat(hdc, pixelFormat, &pfd))
	{
		ReleaseDC(hwnd, hdc);
		DestroyWindow(hwnd);
		UnregisterClass(className, hInstance);
		return false;
	}

	HGLRC hglrc = wglCreateContext(hdc);
	if (hglrc == NULL)
	{
		ReleaseDC(hwnd, hdc);
		DestroyWindow(hwnd);
		UnregisterClass(className, hInstance);
		return false;
	}

	wglMakeCurrent(hdc, hglrc);

	wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARB)wglGetProcAddress("wglChoosePixelFormatARB");
	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARB)wglGetProcAddress("wglCreateContextAttribsARB");

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hglrc);
	ReleaseDC(hwnd, hdc);
	DestroyWindow(hwnd);
	UnregisterClass(className, hInstance);
	return true;
}