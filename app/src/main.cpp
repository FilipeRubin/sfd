#include "graphics-window.h"
#include <math/matrix4x4.h>
#include <math/vector2.h>
#include "3d-data.h"

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
	rr->Bind();
	Matrix4x4 perspective = Matrix4x4::Perspective(16.f / 9.f, 3.1415926 / 2.f, 0.1f, 1000.0f);
	rr->SetProjection(perspective);

	Vector3 camPos;
	Vector2 camRot;
	
	float camSpeed = 0.01f;

	const IBasicInput* input = gw.GetWindow()->GetBasicInput();

	IBasic3DMesh* mesh = rm->CreateBasic3DMesh(planeVertices, sizeof(planeVertices), planeIndices, sizeof(planeIndices));
	ITexture2D* texture = rm->CreateTexture2D(textureData, sizeof(textureData), {10, 1});

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
		rr->SetTexture(texture);
		rr->SetModel(Matrix4x4::Translation({ 0.0f, 0.0f, -5.0f }));
		mesh->Draw();
		gw.EndDraw();
	}

	gw.Finalize();

	return 0;
}
