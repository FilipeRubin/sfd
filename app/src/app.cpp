#include "app.h"
#include "3d-data.h"

IRenderer* renderer = nullptr;
IRendererResourceManager* resourceManager = nullptr;
IWindow* window = nullptr;
IBasicInput* input = nullptr;

IRenderingRule* lambertRenderingRule = nullptr;
IRenderingRule* redRenderingRule = nullptr;
IMesh3D* cubeMesh = nullptr;
ITexture2D* cubeTexture = nullptr;

bool useLambertRenderingRule = true;

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
	lambertRenderingRule = renderer->GetResourceManager()->CreateLambertRenderingRule();
	redRenderingRule = renderer->GetResourceManager()->CreateRedRenderingRule();
	cubeTexture = GeneratePatternTexture(resourceManager, 16, 16);
	cubeMesh = resourceManager->Create3DMesh(cubeVertices, sizeof(cubeVertices), cubeIndices, sizeof(cubeIndices));
}

void App::Update()
{
	if (useLambertRenderingRule)
		lambertRenderingRule->Bind();
	else
		redRenderingRule->Bind();
	cubeTexture->Bind();
	cubeMesh->Draw();

	if (input->IsKeyJustPressed(0x20))
	{
		useLambertRenderingRule = not useLambertRenderingRule;
	}
}
