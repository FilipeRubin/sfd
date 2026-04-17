#include "graphics-window.h"
#include <math/matrix4x4.h>
#include <math/vector2.h>
#include <types/color8.h>
#include "3d-data.h"
#include <assert.h>
#include <iostream>

unsigned char ComputeMiddleGradient(unsigned int stride, unsigned int value)
{
	const bool evenStride = stride % 2 == 0;
	const int transformedValue = value - (stride / 2);
	const bool negativeValue = transformedValue < 0;
	const int index = abs(evenStride and negativeValue ? int(value + 1 - (stride / 2)) : transformedValue);
	const int indexMultiplier = evenStride ?
		(255 / (stride / 2 - 1)) :
		(255 / (stride / 2));
	return index * indexMultiplier;
}

ITexture2D* GeneratePatternTexture(IRendererResourceManager* rm, int width, int height)
{
	Color8* pixels = new Color8[width * height];

	for (int i = 0; i < width; i++)
	{
		for (int j = height - 1; j >= 0; j--)
		{
			pixels[(j * width) + i] = Color8(255 / width * i, 255 / height * j, (255 / width * i + 255 / height * j) / 2);
		}
	}
	
	ITexture2D* result = rm->CreateTexture2D(pixels, sizeof(pixels[0]) * width * height, Dimensions(width, height));

	delete[] pixels;

	return result;
}

ITexture2D* GeneratePatternTexture2(IRendererResourceManager* rm, int width, int height)
{
	Color8* pixels = new Color8[width * height];

	for (int i = 0; i < width; i++)
	{
		for (int j = height - 1; j >= 0; j--)
		{
			pixels[(j * width) + i] = Color8(
				ComputeMiddleGradient(width, i),
				ComputeMiddleGradient(height, j),
				0
			);
		}
	}

	ITexture2D* result = rm->CreateTexture2D(pixels, sizeof(pixels[0]) * width * height, Dimensions(width, height));

	delete[] pixels;

	return result;
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
	ILambertRenderingRule* rr = rm->CreateLambertRenderingRule();
	gw.GetGraphicsBackend()->MakeCurrent();
	gw.GetGraphicsBackend()->GetRenderer()->SetClearColor(0.1f, 0.1f, 0.15f);
	gw.GetGraphicsBackend()->GetRenderer()->BindRenderingRule(rr);
	Matrix4x4 perspective = Matrix4x4::Perspective(16.f / 9.f, 3.1415926 / 2.f, 0.1f, 1000.0f);
	rr->SetProjection(perspective);

	Vector3 camPos;
	Vector2 camRot;
	
	float camSpeed = 0.01f;

	const IBasicInput* input = gw.GetWindow()->GetBasicInput();

	IMesh3D* mesh = rm->Create3DMesh(planeVertices, sizeof(planeVertices), planeIndices, sizeof(planeIndices));
	ITexture2D* textures[100];
	for (int i = 0; i < 100; i++)
		textures[i] = GeneratePatternTexture2(rm, 10 * (i + 1), 10 * (i + 1));

	while (not gw.ShouldClose())
	{
		// Input
		if (input->IsKeyDown(0x25)) // Left
		{
			camRot.y -= 0.001;
		}
		if (input->IsKeyDown(0x26)) // Up
		{
			camRot.x -= 0.001;
		}
		if (input->IsKeyDown(0x27)) // Right
		{
			camRot.y += 0.001;
		}
		if (input->IsKeyDown(0x28)) // Down
		{
			camRot.x += 0.001;
		}
		if (input->IsKeyDown(0x57)) // W
		{
			camPos.x += (-sinf(camRot.y) * camSpeed);
			camPos.z += (cosf(camRot.y) * camSpeed);
			camPos.y += (sinf(camRot.x) * camSpeed);
		}
		if (input->IsKeyDown(0x53)) // S
		{
			camPos.x -= (-sinf(camRot.y) * camSpeed);
			camPos.z -= (cosf(camRot.y) * camSpeed);
			camPos.y -= (sinf(camRot.x) * camSpeed);
		}
		if (input->IsKeyDown(0x41)) // A
		{
			camPos.x += (cosf(camRot.y) * camSpeed);
			camPos.z += (sinf(camRot.y) * camSpeed);
		}
		if (input->IsKeyDown(0x44)) // D
		{
			camPos.x -= (cosf(camRot.y) * camSpeed);
			camPos.z -= (sinf(camRot.y) * camSpeed);
		}
		if (input->IsKeyDown(0x10)) // LShift
		{
			camPos.y += camSpeed;
		}
		if (input->IsKeyDown(0x20)) // Space
		{
			camPos.y -= camSpeed;
		}

		// Camera
		Matrix4x4 viewMatrixRot = Matrix4x4::RotationX(camRot.x) * Matrix4x4::RotationY(camRot.y);
		Matrix4x4 viewMatrixTrans = Matrix4x4::Translation(camPos);
		Matrix4x4 viewMatrix = viewMatrixRot * viewMatrixTrans;
		rr->SetView(viewMatrix);

		// Rendering
		gw.BeginDraw();
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				rr->SetTexture(textures[i*10 + j]);
				rr->SetModel(Matrix4x4::Translation({ (float(i) * 21.0f), -1.0f, float(j) * 21.0f}));
				mesh->Draw();
			}
		}
		gw.EndDraw();
	}

	gw.Finalize();

	return 0;
}
