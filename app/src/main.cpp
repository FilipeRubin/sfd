#include "graphics-window.h"
#include "app.h"

bool TryInitializeGraphicsWindow(GraphicsWindow& graphicsWindow);

int main()
{
	GraphicsWindow graphicsWindow;
	if (not TryInitializeGraphicsWindow(graphicsWindow))
	{
		return -1;
	}

	App::Init(graphicsWindow);
	App::Start();

	while (not graphicsWindow.ShouldClose())
	{
		graphicsWindow.BeginDraw();
		App::Update();
		graphicsWindow.EndDraw();
	}

	return 0;
}

bool TryInitializeGraphicsWindow(GraphicsWindow& graphicsWindow)
{
	WindowParameters params = WindowParameters();
	params.title = L"Game";
	params.width = 1280;
	params.height = 720;
	if (not graphicsWindow.TryInitialize(params))
	{
		return false;
	}

	graphicsWindow.GetGraphicsBackend()->MakeCurrent();

	return true;
}