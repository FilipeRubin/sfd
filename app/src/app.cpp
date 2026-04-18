#include "app.h"
#include "3d-data.h"

IRenderer* renderer = nullptr;
IRendererResourceManager* resourceManager = nullptr;
IWindow* window = nullptr;
IBasicInput* input = nullptr;

ILambertRenderingRule* renderingRule = nullptr;
IMesh3D* cubeMesh = nullptr;
ITexture2D* cubeTexture = nullptr;
float cubeRotation = 0.0f;

void App::Init(GraphicsWindow& graphicsWindow)
{
	renderer = graphicsWindow.GetGraphicsBackend()->GetRenderer();
	resourceManager = renderer->GetResourceManager();
	window = graphicsWindow.GetWindow();
	input = window->GetBasicInput();
}

void App::Start()
{
	renderer->SetClearColor(0.05f, 0.1f, 0.2f);
	renderingRule = renderer->GetResourceManager()->CreateLambertRenderingRule();
	cubeTexture = GeneratePatternTexture(resourceManager, 16, 16);
	cubeMesh = resourceManager->Create3DMesh(cubeVertices, sizeof(cubeVertices), cubeIndices, sizeof(cubeIndices));
	renderingRule->Bind();
	DirectionalLight directionalLight = DirectionalLight();
	directionalLight.ambient = Color(0.0f, 0.0f, 0.0f);
	directionalLight.diffuse = Color(1.0f, 1.0f, 1.0f);
	directionalLight.direction = Vector3(0.0f, -1.0f, -1.0f);
	renderingRule->SetDirectionalLight(directionalLight);
}

void App::Update()
{
	renderingRule->Bind();
	renderingRule->SetProjection(Matrix4x4::Perspective(window->GetAspectRatio(), 3.1415f / 2.0f, 0.1f, 100.0f));
	renderingRule->SetView(Matrix4x4::RotationX(3.1415 / 4.0f) * Matrix4x4::Translation({ 0.0f, -10.0f, -10.0f }));
	renderingRule->SetModel(Matrix4x4::RotationY(cubeRotation));
	cubeTexture->Bind();
	cubeMesh->Draw();
	cubeRotation += 0.001f;
}
