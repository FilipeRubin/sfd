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

typedef void          (*PFNGLATTACHSHADERPROC)(GLuint program, GLuint shader);
typedef void          (*PFNGLBINDBUFFERPROC)(GLenum target, GLuint buffer);
typedef void          (*PFNGLBINDVERTEXARRAYPROC)(GLuint array);
typedef void          (*PFNGLBUFFERDATAPROC)(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage);
typedef void          (*PFNGLCLEARPROC)(GLbitfield mask);
typedef void          (*PFNGLCLEARCOLORPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void          (*PFNGLCOMPILESHADERPROC)(GLuint shader);
typedef GLuint        (*PFNGLCREATEPROGRAMPROC)();
typedef GLuint        (*PFNGLCREATESHADERPROC)(GLenum shaderType);
typedef void          (*PFNGLDELETEBUFFERSPROC)(GLsizei n, GLuint* buffers);
typedef void          (*PFNGLDELETEPROGRAMPROC)(GLuint program);
typedef void          (*PFNGLDELETESHADERPROC)(GLuint shader);
typedef void          (*PFNGLDELETEVERTEXARRAYSPROC)(GLsizei n, GLuint* arrays);
typedef void          (*PFNGLDRAWARRAYSPROC)(GLenum mode, GLint first, GLsizei count);
typedef void          (*PFNGLENABLEVERTEXATTRIBARRAYPROC)(GLuint index);
typedef void          (*PFNGLGENBUFFERSPROC)(GLsizei n, GLuint* buffers);
typedef void          (*PFNGLGENVERTEXARRAYSPROC)(GLsizei n, GLuint* arrays);
typedef const GLubyte*(*PFNGLGETSTRINGPROC)(GLenum name);
typedef GLint         (*PFNGLGETUNIFORMLOCATIONPROC)(GLuint program, const GLchar* name);
typedef GLboolean     (*PFNGLISPROGRAMPROC)(GLuint program);
typedef GLboolean     (*PFNGLISVERTEXARRAYPROC)(GLuint array);
typedef void          (*PFNGLLINKPROGRAMPROC)(GLuint program);
typedef void          (*PFNGLSHADERSOURCEPROC)(GLuint shader, GLsizei count, const GLchar** string, const GLint* length);
typedef void          (*PFNGLUNIFORM3FPROC)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void          (*PFNGLUSEPROGRAMPROC)(GLuint program);
typedef void          (*PFNGLVERTEXATTRIBPOINTERPROC)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer);

void          (*glAttachShader)(GLuint program, GLuint shader);
void          (*glBindBuffer)(GLenum target, GLuint buffer);
void          (*glBindVertexArray)(GLuint array);
void          (*glBufferData)(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage);
void          (*glClear)(GLbitfield mask);
void          (*glClearColor)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
void          (*glCompileShader)(GLuint shader);
GLuint        (*glCreateProgram)();
GLuint        (*glCreateShader)(GLenum shaderType);
void          (*glDeleteBuffers)(GLsizei n, GLuint* arrays);
void          (*glDeleteProgram)(GLuint program);
void          (*glDeleteShader)(GLuint shader);
void          (*glDeleteVertexArrays)(GLsizei n, GLuint* arrays);
void          (*glDrawArrays)(GLenum mode, GLint first, GLsizei count);
void          (*glEnableVertexAttribArray)(GLuint index);
void          (*glGenBuffers)(GLsizei n, GLuint* buffers);
void          (*glGenVertexArrays)(GLsizei n, GLuint* arrays);
const GLubyte*(*glGetString)(GLenum name);
GLint         (*glGetUniformLocation)(GLuint program, const GLchar* name);
GLboolean     (*glIsProgram)(GLuint program);
GLboolean     (*glIsVertexArray)(GLuint array);
void          (*glLinkProgram)(GLuint program);
void          (*glShaderSource)(GLuint shader, GLsizei count, const GLchar** string, const GLint* length);
void          (*glUseProgram)(GLuint program);
void          (*glUniform3f)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
void          (*glVertexAttribPointer)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer);

static bool TryLoadExtFunctions();
static void LoadOGLFuncs();

bool TryLoadOGL()
{
	if (s_glLib != NULL)
		return true;

	s_glLib = LoadLibrary(L"opengl32.dll");

	if (s_glLib == NULL)
		return false;

	if (not TryLoadExtFunctions())
	{
		return false;
	}

	return true;
}

const void* CreateContext(const void* windowHandle, const void* sharedContext)
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
	HGLRC hglrc = wglCreateContextAttribsARB(hdc, (HGLRC)sharedContext, contextAttribs);

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

	LoadOGLFuncs();

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hglrc);
	ReleaseDC(hwnd, hdc);
	DestroyWindow(hwnd);
	UnregisterClass(className, hInstance);
	return true;
}

static void LoadOGLFuncs()
{
	glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
	glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");
	glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
	glClear = (PFNGLCLEARPROC)GetProcAddress(s_glLib, "glClear");
	glClearColor = (PFNGLCLEARCOLORPROC)GetProcAddress(s_glLib, "glClearColor");
	glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
	glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
	glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");
	glDeleteProgram = (PFNGLDELETEPROGRAMPROC)wglGetProcAddress("glDeleteProgram");
	glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
	glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)wglGetProcAddress("glDeleteVertexArrays");
	glDrawArrays = (PFNGLDRAWARRAYSPROC)wglGetProcAddress("glDrawArrays");
	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
	glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
	glGetString = (PFNGLGETSTRINGPROC)GetProcAddress(s_glLib, "glGetString");
	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
	glIsProgram = (PFNGLISPROGRAMPROC)wglGetProcAddress("glIsProgram");
	glIsVertexArray = (PFNGLISVERTEXARRAYPROC)wglGetProcAddress("glIsVertexArray");
	glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
	glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
	glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
	glUniform3f = (PFNGLUNIFORM3FPROC)wglGetProcAddress("glUniform3f");
	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
}
