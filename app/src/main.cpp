#include "graphics-window.h"
#include <math/matrix4x4.h>
#include <math/vector2.h>

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

static float bigBox[]
{
	//   X       Y       Z      R     G     B

	-15.0f, -15.0f, -15.0f,  1.0f, 0.2f, 0.7f, // 0
	 15.0f, -15.0f, -15.0f,  0.3f, 1.0f, 0.1f, // 1
	 15.0f,  15.0f, -15.0f,  0.9f, 0.4f, 0.2f, // 2
	-15.0f,  15.0f, -15.0f,  0.2f, 0.8f, 1.0f, // 3

	-15.0f, -15.0f,  15.0f,  0.6f, 0.1f, 0.9f, // 4
	 15.0f, -15.0f,  15.0f,  0.1f, 0.9f, 0.5f, // 5
	 15.0f,  15.0f,  15.0f,  1.0f, 0.6f, 0.0f, // 6
	-15.0f,  15.0f,  15.0f,  0.4f, 0.3f, 1.0f  // 7
};

static unsigned int bigBoxIndices[]
{
	// back face
	0, 1, 2,
	0, 2, 3,

	// front face
	4, 6, 5,
	4, 7, 6,

	// left face
	0, 3, 7,
	0, 7, 4,

	// right face
	1, 5, 6,
	1, 6, 2,

	// bottom face
	0, 4, 5,
	0, 5, 1,

	// top face
	3, 2, 6,
	3, 6, 7
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
	IBasic3DMesh* mesh2 = rm->CreateBasic3DMesh(bigBox, sizeof(bigBox), bigBoxIndices, sizeof(bigBoxIndices));
	gw.GetGraphicsBackend()->MakeCurrent();
	rr->Bind();
	Matrix4x4 perspective = Matrix4x4::Perspective(16.f / 9.f, 3.1415926 / 2.f, 0.1f, 30.0f);
	rr->SetProjection(perspective);

	float rotY = 0.0f;

	//Vector3 camPos;
	Vector2 camRot;

	const IBasicInput* input = gw.GetWindow()->GetBasicInput();

	while (not gw.ShouldClose())
	{
		// Input
		if (input->IsKeyDown(0x25)) // Left
		{
			camRot.x -= 0.001;
		}
		if (input->IsKeyDown(0x26)) // Up
		{
			camRot.y -= 0.001;
		}
		if (input->IsKeyDown(0x27)) // Right
		{
			camRot.x += 0.001;
		}
		if (input->IsKeyDown(0x28)) // Down
		{
			camRot.y += 0.001;
		}

		// Transforming
		Matrix4x4 trans = Matrix4x4::Translation({ 0.0f, 0.0f, -5.0f });
		Matrix4x4 rot = Matrix4x4::RotationY(rotY);
		rotY += 0.0002f;

		Matrix4x4 viewMatrix = Matrix4x4::RotationX(camRot.y) * Matrix4x4::RotationY(camRot.x);
		rr->SetView(viewMatrix);

		// Rendering
		gw.BeginDraw();
		rr->SetModel(Matrix4x4::Identity());
		mesh2->Draw();
		rr->SetModel(trans * rot);
		mesh->Draw();
		gw.EndDraw();
	}

	gw.Finalize();

	return 0;
}
