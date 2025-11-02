#include "graphics-window.h"
#include <math/matrix4x4.h>
#include <iostream>
#include <iomanip>

void printMatrix(const Matrix4x4& matrix)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			std::cout << std::setw(3) << (int)matrix[j][i] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int main()
{
	Matrix4x4 m1 = {
		{ 1, 0, 2, 1 },
		{ 2, 1, 3, 5 },
		{ 3, 0, 4, 1 },
		{ 4, 1, 7, 1 }
	};
	Matrix4x4 m2 = {
		{ 1, 2, 3, 4 },
		{ 1, 2, 1, 1 },
		{ 3, 1, 4, 1 },
		{ 2, 3, 6, 5 }
	};

	Matrix4x4 m3 = m1 * m2;

	printMatrix(m3);

	/*GraphicsWindow gw1 = GraphicsWindow();
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

		float square[] = {
			0.5f, -0.5f,
			0.5f, 0.5f,
			-0.5f, -0.5f,
			-0.5f, -0.5f,
			0.5f, 0.5f,
			-0.5f, 0.5f
		};

		IRendererResourceManager* rm = gw1.GetGraphicsBackend()->GetRenderer()->GetResourceManager();
		INDCRenderingRule* rr = rm->CreateNDCRenderingRule();
		INDCShape* shape = rm->CreateNDCShape(triangle, sizeof(triangle));

		IRendererResourceManager* rm2 = gw2.GetGraphicsBackend()->GetRenderer()->GetResourceManager();
		INDCRenderingRule* rr2 = rm2->CreateNDCRenderingRule();
		INDCShape* shape2 = rm2->CreateNDCShape(square, sizeof(square));
		while (GraphicsWindow::IsAnyWindowOpen())
		{
			if (gw1.IsInitialized())
				if (gw1.ShouldClose()) gw1.Finalize();
				else
				{
					gw1.BeginDraw();
					rr->Bind();
					rr->SetColor(0.1f, 0.5f, 0.7f);
					shape->Draw();
					gw1.EndDraw();
				}

			if (gw2.IsInitialized())
				if (gw2.ShouldClose()) gw2.Finalize();
				else
				{
					gw2.BeginDraw();
					rr2->Bind();
					rr2->SetColor(0.75f, 0.7f, 0.65f);
					shape2->Draw();
					gw2.EndDraw();
				}
		}
	}

	gw1.Finalize();
	gw2.Finalize();*/

	return 0;
}