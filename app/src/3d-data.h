#pragma once
#include <types/vertex-3d.h>

static alignas(4) Vertex3D planeVertices[]{
	{ {  10.0f, 0.0f,  10.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f } },
	{ {  10.0f, 0.0f, -10.0f }, { 0.0f, 1.0f, 1.0f }, { 1.0f, 1.0f } },
	{ { -10.0f, 0.0f, -10.0f }, { 1.0f, 0.0f, 1.0f }, { 0.0f, 1.0f } },
	{ { -10.0f, 0.0f,  10.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f } }
};

static unsigned int planeIndices[]{
	0U, 1U, 2U,
	0U, 2U, 3U
};

static unsigned char textureData[] = {
	250, 255, 255, 255,
	225, 255, 255, 255,
	200, 255, 255, 255,
	175, 255, 255, 255,
	150, 255, 255, 255,
	125, 255, 255, 255,
	100, 255, 255, 255,
	 75, 255, 255, 255,
	 50, 255, 255, 255,
	  0, 255, 255, 255,
};
