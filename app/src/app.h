#pragma once
#include "graphics-window.h"

class App
{
public:
	void Init(GraphicsWindow& graphicsWindow);
	void Start();
	void Update();
private:
	IRenderer* renderer = nullptr;
	IRendererResourceManager* resourceManager = nullptr;
	IWindow* window = nullptr;
	IBasicInput* input = nullptr;

	IRenderingRule* lambertRenderingRule = nullptr;
	IRenderingRule* unshadedRenderingRule = nullptr;
	IRenderingRule* currentRenderingRule = nullptr;
	IMesh3D* cubeMesh = nullptr;
	IMesh3D* planeMesh = nullptr;
	ITexture2D* cubeTexture = nullptr;
	ITexture2D* planeTexture = nullptr;

	ICamera3DParameter* cameraParameter = nullptr;
	IDirectionalLightParameter* lightParameter = nullptr;
	ITransform3DParameter* cubeTransformParameter = nullptr;
	ITransform3DParameter* planeTransformParameter = nullptr;

	bool useLambertRenderingRule = true;

	float lightRotation = 0.0f;
	float cubeHeightOffset = 0.0f;
};