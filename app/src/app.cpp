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
	Dimensions terrainGrid = { 500, 500 };
	size_t terrainDataSize = terrainGrid.width * terrainGrid.height;
	Shared<FixedArray<float>> terrainData = Shared<FixedArray<float>>(new FixedArray<float>(terrainDataSize));

	srand(time(NULL));
	for (size_t i = 0; i < terrainDataSize; i++)
	{
		const float height = float((rand() % 100) + 1.0f) / 100.0f;
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
	cameraParameter->Camera().position = Vector3(0.0f, -5.0f, 0.0f);

	lightParameter->Light().ambient = Color(0.05f, 0.05f, 0.2f);
	lightParameter->Light().diffuse = Color(1.0f, 0.85f, 0.7f);

	transformParameter->Transform().scale = {200.0f, 1.0f, 200.0f};
	transformParameter->Transform().position = {
		-transformParameter->Transform().scale.x / 2.0f,
		0.0f,
		-transformParameter->Transform().scale.z / 2.0f 
	};
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
	
	if (input->IsKeyDown(0x41)) // A
		transformParameter->Transform().position.x -= 1.5f * deltaTime;
	if (input->IsKeyDown(0x44)) // D
		transformParameter->Transform().position.x += 1.5f * deltaTime;
	if (input->IsKeyDown(0x57)) // W
		transformParameter->Transform().position.z += 1.5f * deltaTime;
	if (input->IsKeyDown(0x53)) // S
		transformParameter->Transform().position.z -= 1.5f * deltaTime;
	if (input->IsKeyDown(0x51)) // Q
		transformParameter->Transform().position.y -= 3.5f * deltaTime;
	if (input->IsKeyDown(0x45)) // E
		transformParameter->Transform().position.y += 3.5f * deltaTime;

	// Animation
	lightParameter->Light().direction = Vector3(sinf(lightRotation), -0.5f, cosf(lightRotation));
	lightRotation += 0.005f * deltaTime;

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
