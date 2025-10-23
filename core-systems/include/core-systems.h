#pragma once
#include "i-window.h"
#include "i-graphics-backend.h"

class CoreSystems final
{
public:
	static IWindow* CreateWindow();
	static IGraphicsBackend* CreateGraphicsBackend(IWindow* window);
};