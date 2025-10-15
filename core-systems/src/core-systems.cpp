#include <core-systems.h>
#include "win32-window.h"

#ifdef _WIN32
typedef Win32Window ConcreteWindow;
#endif // _WIN32

IWindow* CoreSystems::CreateWindow()
{
	return new ConcreteWindow();
}
