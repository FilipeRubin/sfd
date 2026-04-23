#include "app.h"
#include "3d-data.h"
#include <rendering/data-generation/mesh-3d/plane-mesh-3d-generator.h>
#include <rendering/data-generation/mesh-3d/cube-mesh-3d-generator.h>
#include <rendering/data-generation/rendering-rule/unshaded-rendering-rule-generator.h>
#include <rendering/data-generation/rendering-rule/lambert-rendering-rule-generator.h>
#include <rendering/data-generation/texture-2d/raw-data-texture-2d-generator.h>

void App::Init(GraphicsWindow& graphicsWindow)
{
	renderer = graphicsWindow.GetGraphicsBackend()->GetRenderer();
	resourceManager = renderer->GetResourceManager();
	window = graphicsWindow.GetWindow();
	input = window->GetBasicInput();
}

void App::Start()
{
	Shared<FixedArray<Color8>> patTexture1 = GeneratePatternTexture(resourceManager, 16, 16);
	Shared<FixedArray<Color8>> patTexture2 = GeneratePatternTexture2(resourceManager, 16, 16);

	lambertRenderingRule = renderer->GetResourceManager()->CreateRenderingRule(LambertRenderingRuleGenerator());
	unshadedRenderingRule = renderer->GetResourceManager()->CreateRenderingRule(UnshadedRenderingRuleGenerator());
	cubeMesh = resourceManager->Create3DMesh(CubeMesh3DGenerator({4.0f, 4.0f, 1.5f}));
	planeMesh = resourceManager->Create3DMesh(PlaneMesh3DGenerator({ 50.0f, 50.0f }));
	cubeTexture = resourceManager->CreateTexture2D(RawDataTexture2DGenerator(patTexture1, {16, 16}));
	planeTexture = resourceManager->CreateTexture2D(RawDataTexture2DGenerator(patTexture1, {16, 16}));

	cameraParameter = renderer->GetParameterManager()->CreateCamera3D();
	lightParameter = renderer->GetParameterManager()->CreateDirectionalLight();
	cubeTransformParameter = renderer->GetParameterManager()->CreateTransform3D();
	planeTransformParameter = renderer->GetParameterManager()->CreateTransform3D();

	cameraParameter->Camera().aspectRatio = window->GetAspectRatio();
	cameraParameter->Camera().vFOV = 3.1415f / 2.0f;
	cameraParameter->Camera().zNear = 0.1f;
	cameraParameter->Camera().zFar = 100.0f;
	cameraParameter->Camera().position = Vector3(0.0f, -10.0f, -10.0f);

	lightParameter->Light().ambient = Color(0.05f, 0.05f, 0.2f);
	lightParameter->Light().diffuse = Color(1.0f, 0.85f, 0.7f);

	cubeTransformParameter->Transform().position = Vector3(-5.0f, 1.5f, -0.5f);
	cubeTransformParameter->Transform().scale = Vector3(4.0f, 3.0f, 3.0f);
}

void App::Update()
{
	// Input
	if (input->IsKeyJustPressed(0x20)) // Spacebar
		useLambertRenderingRule = not useLambertRenderingRule;
	if (input->IsKeyDown(0x25)) // Left
		cameraParameter->Camera().rotation.y -= 0.001f;
	if (input->IsKeyDown(0x26)) // Up
		cameraParameter->Camera().rotation.x -= 0.001f;
	if (input->IsKeyDown(0x27)) // Right
		cameraParameter->Camera().rotation.y += 0.001f;
	if (input->IsKeyDown(0x28)) // Down
		cameraParameter->Camera().rotation.x += 0.001f;

	// Animation
	cubeTransformParameter->Transform().position.y = 3.0f + (sinf(cubeHeightOffset) * 1.75f);
	cubeTransformParameter->Transform().rotation.y += 0.00015f;
	lightParameter->Light().direction = Vector3(sinf(lightRotation), -0.5f, cosf(lightRotation));
	lightRotation += 0.0005f;
	cubeHeightOffset += 0.001f;

	// Rule binding
	if (useLambertRenderingRule)
	{
		currentRenderingRule = lambertRenderingRule;
		renderer->SetClearColor({ 0.05f, 0.1f, 0.2f });
	}
	else
	{
		currentRenderingRule = unshadedRenderingRule;
		renderer->SetClearColor({ 0.1f, 0.2f, 0.4f });
	}
	currentRenderingRule->Bind();
	
	// State updating
	cameraParameter->Camera().aspectRatio = window->GetAspectRatio();

	// State binding
	cameraParameter->Bind(currentRenderingRule);
	lightParameter->Bind(currentRenderingRule);

	// Drawing
	cubeTransformParameter->Bind(currentRenderingRule);
	cubeTexture->Bind();
	cubeMesh->Draw();
	planeTransformParameter->Bind(currentRenderingRule);
	planeTexture->Bind();
	planeMesh->Draw();
}
