#include "app.h"
#include "3d-data.h"
#include <rendering/data-generation/mesh-3d/plane-mesh-3d-generator.h>
#include <rendering/data-generation/mesh-3d/cube-mesh-3d-generator.h>
#include <rendering/data-generation/mesh-3d/terrain-mesh-3d-generator.h>
#include <rendering/data-generation/rendering-rule/unshaded-rendering-rule-generator.h>
#include <rendering/data-generation/rendering-rule/lambert-rendering-rule-generator.h>
#include <rendering/data-generation/texture-2d/raw-data-texture-2d-generator.h>
#include <rendering/data-generation/texture-2d/checkerboard-texture-2d-generator.h>

void App::Init(GraphicsWindow& graphicsWindow)
{
	renderer = graphicsWindow.GetGraphicsBackend()->GetRenderer();
	resourceManager = renderer->GetResourceManager();
	window = graphicsWindow.GetWindow();
	input = window->GetBasicInput();
	lastTime = window->GetTime();
}

void App::Start()
{
	Dimensions terrainGrid = { 10, 10 };
	size_t terrainDataSize = terrainGrid.width * terrainGrid.height;
	Shared<FixedArray<float>> terrainData = Shared<FixedArray<float>>(new FixedArray<float>(terrainDataSize));
	for (size_t i = 0; i < terrainDataSize; i++)
	{
		const size_t x = i % terrainGrid.width;
		const size_t y = i / terrainGrid.width;
		const float heightX = fabsf((float)x - (float)terrainGrid.width / 2.0f) / ((float)terrainGrid.width / 2.0f);
		const float heightY = fabsf((float)y - (float)terrainGrid.height / 2.0f) / ((float)terrainGrid.height / 2.0f);
		const float height = (heightX + heightY) * 2.0f;
		(*terrainData)[i] = height;
	}

	Shared<FixedArray<Color8>> patTexture1 = GeneratePatternTexture(resourceManager, 16, 16);
	Shared<FixedArray<Color8>> patTexture2 = GeneratePatternTexture2(resourceManager, 16, 16);

	lambertRenderingRule = renderer->GetResourceManager()->CreateRenderingRule(LambertRenderingRuleGenerator());
	unshadedRenderingRule = renderer->GetResourceManager()->CreateRenderingRule(UnshadedRenderingRuleGenerator());
	terrainMesh = resourceManager->Create3DMesh(TerrainMesh3DGenerator(terrainGrid, terrainData));
	terrainTexture = resourceManager->CreateTexture2D(RawDataTexture2DGenerator(patTexture1, {16, 16}));

	cameraParameter = renderer->GetParameterManager()->CreateCamera3D();
	lightParameter = renderer->GetParameterManager()->CreateDirectionalLight();
	transformParameter = renderer->GetParameterManager()->CreateTransform3D();

	cameraParameter->Camera().aspectRatio = window->GetAspectRatio();
	cameraParameter->Camera().vFOV = 3.1415f / 2.0f;
	cameraParameter->Camera().zNear = 0.1f;
	cameraParameter->Camera().zFar = 100.0f;
	cameraParameter->Camera().position = Vector3(0.0f, -10.0f, 0.0f);

	lightParameter->Light().ambient = Color(0.05f, 0.05f, 0.2f);
	lightParameter->Light().diffuse = Color(1.0f, 0.85f, 0.7f);

	transformParameter->Transform().position = { -2.5f, 0.0f, -2.5f };
	transformParameter->Transform().scale = {10.0f, 1.0f, 10.0f};
}

void App::Update()
{
	const float deltaTime = window->GetTime() - lastTime;
	lastTime = window->GetTime();

	// Input
	if (input->IsKeyJustPressed(0x20)) // Spacebar
		useLambertRenderingRule = not useLambertRenderingRule;
	if (input->IsKeyDown(0x25)) // Left
		cameraParameter->Camera().rotation.y -= 0.75f * deltaTime;
	if (input->IsKeyDown(0x26)) // Up
		cameraParameter->Camera().rotation.x -= 0.75f * deltaTime;
	if (input->IsKeyDown(0x27)) // Right
		cameraParameter->Camera().rotation.y += 0.75f * deltaTime;
	if (input->IsKeyDown(0x28)) // Down
		cameraParameter->Camera().rotation.x += 0.75f * deltaTime;

	// Animation
	lightParameter->Light().direction = Vector3(sinf(lightRotation), -0.5f, cosf(lightRotation));
	lightRotation += 0.005f * deltaTime;
	transformParameter->Transform().scale.y = lightRotation * 20.0f;

	// Rule binding
	if (useLambertRenderingRule and lambertRenderingRule != nullptr)
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
	transformParameter->Bind(currentRenderingRule);
	terrainTexture->Bind();
	terrainMesh->Draw();
}
