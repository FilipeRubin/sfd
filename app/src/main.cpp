#include "graphics-window.h"

int main()
{
	GraphicsWindow gw1 = GraphicsWindow();
	GraphicsWindow gw2 = GraphicsWindow();
	if (not gw1.TryInitialize({
		.title = L"Game window",
		.width = 1280,
		.height = 720
		}))
	{
		return 1;
	}

	if (not gw2.TryInitialize({
		.title = L"Debug window",
		.width = 640,
		.height = 480
		}))
	{
		gw1.Finalize();
		return 2;
	}
	
	while (GraphicsWindow::IsAnyWindowOpen())
	{
		if (gw1.IsInitialized())
			if (gw1.ShouldClose())
				gw1.Finalize();
			else
				gw1.Draw(0.1f, 0.45f, 0.95f);

		if (gw2.IsInitialized())
			if (gw2.ShouldClose())
				gw2.Finalize();
			else
				gw2.Draw(0.9f, 0.65f, 0.05f);
	}

	gw1.Finalize();
	gw2.Finalize();

	return 0;
}