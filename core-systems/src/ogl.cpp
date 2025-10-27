#include "ogl.h"
#include <Windows.h>

static HMODULE s_glLib = NULL;

typedef const GLubyte*(*PFNGLGETSTRINGPROC)(GLenum name);

PFNGLGETSTRINGPROC glGetString;

bool TryLoadOGL()
{
	if (s_glLib != NULL)
		return true;

	s_glLib = LoadLibrary(L"opengl32.dll");

	if (s_glLib == NULL)
		return false;

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
