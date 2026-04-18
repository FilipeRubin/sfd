#pragma once
#include <rendering/resources/i-texture-2d.h>
#include <rendering/i-renderer-resource-manager.h>
#include <types/vertex-3d.h>
#include <types/color8.h>

static Vertex3D planeVertices[]{
	{ {  10.0f, 0.0f,  10.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } },
	{ {  10.0f, 0.0f, -10.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f } },
	{ { -10.0f, 0.0f, -10.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f } },
	{ { -10.0f, 0.0f,  10.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f } }
};

static unsigned int planeIndices[]{
	0U, 1U, 2U,
	0U, 2U, 3U
};

static Vertex3D cubeVertices[] =
{
	// Front (+Z)
	{ { -5.0f, -5.0f,  5.0f }, { 0, 0, 1 }, { 0, 0 } },
	{ {  5.0f, -5.0f,  5.0f }, { 0, 0, 1 }, { 1, 0 } },
	{ {  5.0f,  5.0f,  5.0f }, { 0, 0, 1 }, { 1, 1 } },
	{ { -5.0f,  5.0f,  5.0f }, { 0, 0, 1 }, { 0, 1 } },

	// Back (-Z)
	{ {  5.0f, -5.0f, -5.0f }, { 0, 0, -1 }, { 0, 0 } },
	{ { -5.0f, -5.0f, -5.0f }, { 0, 0, -1 }, { 1, 0 } },
	{ { -5.0f,  5.0f, -5.0f }, { 0, 0, -1 }, { 1, 1 } },
	{ {  5.0f,  5.0f, -5.0f }, { 0, 0, -1 }, { 0, 1 } },

	// Left (-X)
	{ { -5.0f, -5.0f, -5.0f }, { -1, 0, 0 }, { 0, 0 } },
	{ { -5.0f, -5.0f,  5.0f }, { -1, 0, 0 }, { 1, 0 } },
	{ { -5.0f,  5.0f,  5.0f }, { -1, 0, 0 }, { 1, 1 } },
	{ { -5.0f,  5.0f, -5.0f }, { -1, 0, 0 }, { 0, 1 } },

	// Right (+X)
	{ {  5.0f, -5.0f,  5.0f }, { 1, 0, 0 }, { 0, 0 } },
	{ {  5.0f, -5.0f, -5.0f }, { 1, 0, 0 }, { 1, 0 } },
	{ {  5.0f,  5.0f, -5.0f }, { 1, 0, 0 }, { 1, 1 } },
	{ {  5.0f,  5.0f,  5.0f }, { 1, 0, 0 }, { 0, 1 } },

	// Top (+Y)
	{ { -5.0f,  5.0f,  5.0f }, { 0, 1, 0 }, { 0, 0 } },
	{ {  5.0f,  5.0f,  5.0f }, { 0, 1, 0 }, { 1, 0 } },
	{ {  5.0f,  5.0f, -5.0f }, { 0, 1, 0 }, { 1, 1 } },
	{ { -5.0f,  5.0f, -5.0f }, { 0, 1, 0 }, { 0, 1 } },

	// Bottom (-Y)
	{ { -5.0f, -5.0f, -5.0f }, { 0, -1, 0 }, { 0, 0 } },
	{ {  5.0f, -5.0f, -5.0f }, { 0, -1, 0 }, { 1, 0 } },
	{ {  5.0f, -5.0f,  5.0f }, { 0, -1, 0 }, { 1, 1 } },
	{ { -5.0f, -5.0f,  5.0f }, { 0, -1, 0 }, { 0, 1 } }
};

static unsigned int cubeIndices[] =
{
	// Front (+Z)
	0, 1, 2,
	2, 3, 0,

	// Back (-Z)
	4, 5, 6,
	6, 7, 4,

	// Left (-X)
	8, 9, 10,
	10, 11, 8,

	// Right (+X)
	12, 13, 14,
	14, 15, 12,

	// Top (+Y)
	16, 17, 18,
	18, 19, 16,

	// Bottom (-Y)
	20, 21, 22,
	22, 23, 20
};

static Color8 textureData[] = {
	Color8(250, 255, 255),
	Color8(225, 255, 255),
	Color8(200, 255, 255),
	Color8(175, 255, 255),
	Color8(150, 255, 255),
	Color8(125, 255, 255),
	Color8(100, 255, 255),
	Color8( 75, 255, 255),
	Color8( 50, 255, 255),
	Color8(  0, 255, 255),

	Color8(250, 255, 255),
	Color8(225, 250, 255),
	Color8(200, 245, 255),
	Color8(175, 240, 255),
	Color8(150, 235, 255),
	Color8(125, 230, 255),
	Color8(100, 225, 255),
	Color8( 75, 220, 255),
	Color8( 50, 215, 255),
	Color8(  0, 210, 255),

	Color8(250, 205, 255),
	Color8(225, 200, 255),
	Color8(200, 195, 255),
	Color8(175, 190, 255),
	Color8(150, 185, 255),
	Color8(125, 180, 255),
	Color8(100, 175, 255),
	Color8( 75, 170, 255),
	Color8( 50, 165, 255),
	Color8(  0, 160, 255),

	Color8(250, 155, 255),
	Color8(225, 150, 255),
	Color8(200, 145, 255),
	Color8(175, 140, 255),
	Color8(150, 135, 255),
	Color8(125, 130, 255),
	Color8(100, 125, 255),
	Color8( 75, 120, 255),
	Color8( 50, 115, 255),
	Color8(  0, 110, 255),

	Color8(250, 105, 255),
	Color8(225, 100, 255),
	Color8(200,  95, 255),
	Color8(175,  90, 255),
	Color8(150,  85, 255),
	Color8(125,  80, 255),
	Color8(100,  75, 255),
	Color8( 75,  70, 255),
	Color8( 50,  65, 255),
	Color8(  0,  60, 255),

	Color8(250,  55, 255),
	Color8(225,  50, 255),
	Color8(200,  45, 255),
	Color8(175,  40, 255),
	Color8(150,  35, 255),
	Color8(125,  30, 255),
	Color8(100,  25, 255),
	Color8( 75,  20, 255),
	Color8( 50,  15, 255),
	Color8(  0,  10, 255),

	Color8(250,   5, 255),
	Color8(225,   0, 255),
	Color8(200,   0, 255),
	Color8(175,   0, 255),
	Color8(150,   0, 255),
	Color8(125,   0, 255),
	Color8(100,   0, 255),
	Color8( 75,   0, 255),
	Color8( 50,   0, 255),
	Color8(  0,   0, 255),

	Color8(250,   0, 255),
	Color8(225,   0, 255),
	Color8(200,   0, 255),
	Color8(175,   0, 255),
	Color8(150,   0, 255),
	Color8(125,   0, 255),
	Color8(100,   0, 255),
	Color8( 75,   0, 255),
	Color8( 50,   0, 255),
	Color8(  0,   0, 255),

	Color8(250,   0, 255),
	Color8(225,   0, 255),
	Color8(200,   0, 255),
	Color8(175,   0, 255),
	Color8(150,   0, 255),
	Color8(125,   0, 255),
	Color8(100,   0, 255),
	Color8( 75,   0, 255),
	Color8( 50,   0, 255),
	Color8(  0,   0, 255),

	Color8(250,   0, 255),
	Color8(225,   0, 255),
	Color8(200,   0, 255),
	Color8(175,   0, 255),
	Color8(150,   0, 255),
	Color8(125,   0, 255),
	Color8(100,   0, 255),
	Color8( 75,   0, 255),
	Color8( 50,   0, 255),
	Color8(  0,   0, 255)
};

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
			Color8& pixel = pixels[(j * width) + i];
			pixel = Color8(255 / width * i, 255 / height * j, (255 / width * i + 255 / height * j) / 2);
			pixel.b = fmax(fmax(255 - pixel.r, 255 - pixel.b), pixel.b);
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
