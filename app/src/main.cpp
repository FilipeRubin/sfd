#include "graphics-window.h"
#include <math/matrix4x4.h>

static float vertices[]
{
	 1.0f, -1.0f, 0.0f, 1.0f, 0.3f, 0.0f,
	 1.0f,  1.0f, 0.0f, 0.0f, 0.3f, 1.0f,
	-1.0f,  1.0f, 0.0f, 0.3f, 1.0f, 0.0f,
	-1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.3f
};

static unsigned int indices[]
{
	0U, 1U, 2U,
	0U, 2U, 3U
};

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
	GraphicsWindow gw = GraphicsWindow();
	WindowParameters wp = WindowParameters();
	wp.title = L"Game";
	wp.width = 1280;
	wp.height = 720;
	if (not gw.TryInitialize(wp))
	{
		return 1;
	}

	IRendererResourceManager* rm = gw.GetGraphicsBackend()->GetRenderer()->GetResourceManager();
	IBasic3DRenderingRule* rr = rm->CreateBasic3DRenderingRule();
	IBasic3DMesh* mesh = rm->CreateBasic3DMesh(vertices, sizeof(vertices), indices, sizeof(indices));
	gw.GetGraphicsBackend()->MakeCurrent();
	rr->Bind();
	Matrix4x4 perspective = Matrix4x4::Perspective(16.f / 9.f, 3.1415926 / 2.f, 0.1f, 10.0f);
	rr->SetProjection(perspective);

	float rotY = 0.0f;

	while (not gw.ShouldClose())
	{
		Matrix4x4 trans = Matrix4x4::Translation({ 0.0f, 0.0f, -5.0f });
		Matrix4x4 rot = Matrix4x4::RotationY(rotY);
		rr->SetModel(trans * rot);

		gw.BeginDraw();
		mesh->Draw();
		gw.EndDraw();

		rotY += 0.0002f;
	}

	gw.Finalize();

	return 0;
}
