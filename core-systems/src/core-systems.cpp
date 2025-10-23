#include <core-systems.h>
#ifdef _WIN32
#include "win32-window.h"
#include "ogl-graphics-backend.h"

IWindow* CoreSystems::CreateWindow()
{
	return new Win32Window();
}

IGraphicsBackend* CoreSystems::CreateGraphicsBackend(IWindow* window)
{
	Win32Window* win32Window = static_cast<Win32Window*>(window);
	return new OGLGraphicsBackend(win32Window->GetHandle());
}
#endif // _WIN32
