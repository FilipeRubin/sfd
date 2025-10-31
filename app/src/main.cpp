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

	gw1.GetGraphicsBackend()->MakeCurrent();
	gw1.GetGraphicsBackend()->GetRenderer()->SetClearColor(1.0f, 0.0f, 0.0f);
	gw2.GetGraphicsBackend()->MakeCurrent();
	gw2.GetGraphicsBackend()->GetRenderer()->SetClearColor(0.0f, 1.0f, 0.0f);

	gw1.GetGraphicsBackend()->MakeCurrent();
	{
		float triangle[] = {
			1.0f, -1.0f,
			0.5f, 0.0f,
			0.0f, -1.0f
		};
		unique_ptr<IDrawable> drawable = unique_ptr<IDrawable>(gw1.GetGraphicsBackend()->GetRenderer()->CreateNDCMesh(triangle, sizeof(triangle)));
		while (GraphicsWindow::IsAnyWindowOpen())
		{
			if (gw1.IsInitialized())
				if (gw1.ShouldClose()) gw1.Finalize();
				else
				{
					gw1.BeginDraw();
					drawable->Draw();
					gw1.EndDraw();
				}

			if (gw2.IsInitialized())
				if (gw2.ShouldClose()) gw2.Finalize();
				else
				{
					gw2.BeginDraw();
					gw2.EndDraw();
				}
		}
	}

	gw1.Finalize();
	gw2.Finalize();

	return 0;
}