#include "ogl.h"
#include <Windows.h>

static HMODULE s_glLib = NULL;

typedef void (*PFNGLCLEARPROC)(GLbitfield mask);
typedef void (*PFNGLCLEARCOLORPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef const GLubyte*(*PFNGLGETSTRINGPROC)(GLenum name);

void (*glClear)(GLbitfield mask);
void (*glClearColor)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
const GLubyte* (*glGetString)(GLenum name);

bool TryLoadOGL()
{
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

void UnloadOGL()
{
	if (s_glLib != NULL)
	{
		FreeLibrary(s_glLib);
		s_glLib = NULL;
	}
}
