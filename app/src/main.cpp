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
	gw1.GetGraphicsBackend()->GetRenderer()->SetClearColor(0.3f, 0.05f, 0.05f);
	gw2.GetGraphicsBackend()->MakeCurrent();
	gw2.GetGraphicsBackend()->GetRenderer()->SetClearColor(0.05f, 0.3f, 0.05f);

	{
		float triangle[] = {
			0.5f, -0.5f,
			0.0f, 0.5f,
			-0.5f, -0.5f
		};
		gw1.GetGraphicsBackend()->MakeCurrent();
		IRendererResourceManager* rm = gw1.GetGraphicsBackend()->GetRenderer()->GetResourceManager();
		INDCRenderingRule* rr = rm->CreateNDCRenderingRule();
		rr->Bind();
		rr->SetColor(0.1f, 0.5f, 0.7f);
		INDCShape* shape = rm->CreateNDCShape(triangle, sizeof(triangle));

		gw2.GetGraphicsBackend()->MakeCurrent();
		IRendererResourceManager* rm2 = gw2.GetGraphicsBackend()->GetRenderer()->GetResourceManager();
		INDCRenderingRule* rr2 = rm2->CreateNDCRenderingRule();
		rr2->Bind();
		rr2->SetColor(0.75f, 0.7f, 0.65f);
		INDCShape* shape2 = rm2->CreateNDCShape(triangle, sizeof(triangle));
		while (GraphicsWindow::IsAnyWindowOpen())
		{
			if (gw1.IsInitialized())
				if (gw1.ShouldClose()) gw1.Finalize();
				else
				{
					gw1.BeginDraw();
					rr->Bind();
					shape->Draw();
					gw1.EndDraw();
				}

			if (gw2.IsInitialized())
				if (gw2.ShouldClose()) gw2.Finalize();
				else
				{
					gw2.BeginDraw();
					rr2->Bind();
					shape2->Draw();
					gw2.EndDraw();
				}
		}
	}

	gw1.Finalize();
	gw2.Finalize();

	return 0;
}