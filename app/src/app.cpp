#include "app.h"
#include "3d-data.h"
#include <rendering/data-generation/mesh-3d/plane-mesh-3d-generator.h>
#include <rendering/data-generation/mesh-3d/cube-mesh-3d-generator.h>
#include <rendering/data-generation/mesh-3d/terrain-mesh-3d-generator.h>
#include <rendering/data-generation/rendering-rule/unshaded-rendering-rule-generator.h>
#include <rendering/data-generation/rendering-rule/lambert-rendering-rule-generator.h>
#include <rendering/data-generation/texture-2d/raw-data-texture-2d-generator.h>
#include <rendering/data-generation/texture-2d/checkerboard-texture-2d-generator.h>

void ProcessHeight(int x, int y, const int maxX, const int maxY, float& height);

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
	const int terrainX = 10;
	const int terrainY = 10;

	Dimensions terrainGrid = { terrainX, terrainY };
	size_t terrainDataSize = terrainGrid.width * terrainGrid.height;
	Shared<FixedArray<float>> terrainData = Shared<FixedArray<float>>(new FixedArray<float>(terrainDataSize));

	for (int i = 0; i < terrainY; i++)
	{
		for (int j = 0; j < terrainX; j++)
		{
			float height = 0.0f;
			ProcessHeight(j, i, terrainX, terrainY, height);
			(*terrainData)[i * terrainX + j] = height;
		}
	}

	Shared<FixedArray<Color8>> patTexture1 = GeneratePatternTexture(resourceManager, 16, 16);
	Shared<FixedArray<Color8>> patTexture2 = GeneratePatternTexture2(resourceManager, 16, 16);

	lambertRenderingRule = renderer->GetResourceManager()->CreateRenderingRule(LambertRenderingRuleGenerator());
	unshadedRenderingRule = renderer->GetResourceManager()->CreateRenderingRule(UnshadedRenderingRuleGenerator());
	terrainMesh = resourceManager->Create3DMesh(TerrainMesh3DGenerator(terrainGrid, terrainData));
	terrainTexture = resourceManager->CreateTexture2D(RawDataTexture2DGenerator(patTexture2, {16, 16}));

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
	if (input->IsKeyJustPressed(KeyboardKey::SPACE))
		useLambertRenderingRule = not useLambertRenderingRule;
	if (input->IsKeyDown(KeyboardKey::LEFT))
		cameraParameter->Camera().rotation.y -= 0.75f * deltaTime;
	if (input->IsKeyDown(KeyboardKey::UP))
		cameraParameter->Camera().rotation.x -= 0.75f * deltaTime;
	if (input->IsKeyDown(KeyboardKey::RIGHT))
		cameraParameter->Camera().rotation.y += 0.75f * deltaTime;
	if (input->IsKeyDown(KeyboardKey::DOWN))
		cameraParameter->Camera().rotation.x += 0.75f * deltaTime;
	
	if (input->IsKeyDown(KeyboardKey::A))
		transformParameter->Transform().position.x -= 1.5f * deltaTime;
	if (input->IsKeyDown(KeyboardKey::D))
		transformParameter->Transform().position.x += 1.5f * deltaTime;
	if (input->IsKeyDown(KeyboardKey::W))
		transformParameter->Transform().position.z += 1.5f * deltaTime;
	if (input->IsKeyDown(KeyboardKey::S))
		transformParameter->Transform().position.z -= 1.5f * deltaTime;
	if (input->IsKeyDown(KeyboardKey::Q))
		cameraParameter->Camera().position.y += 3.5f * deltaTime;
	if (input->IsKeyDown(KeyboardKey::E))
		cameraParameter->Camera().position.y -= 3.5f * deltaTime;

	if (input->IsMouseButtonJustPressed(MouseButton::LEFT))
		transformParameter->Transform().position.y += 1.0f;
	else if (input->IsMouseButtonJustPressed(MouseButton::RIGHT))
		transformParameter->Transform().position.y -= 1.0f;
	if (input->IsMouseButtonJustReleased(MouseButton::MOUSE4))
		transformParameter->Transform().scale.x += 1.0f;
	else if (input->IsMouseButtonJustReleased(MouseButton::MOUSE5))
		transformParameter->Transform().scale.z += 1.0f;
	if (input->IsMouseButtonJustPressed(MouseButton::MIDDLE))
		transformParameter->Transform().scale = { 1.0f, 1.0f, 1.0f };
	
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

void ProcessHeight(int x, int y, const int maxX, const int maxY, float& height)
{
	height = float(x) / maxX;
}
