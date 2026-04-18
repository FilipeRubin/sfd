#pragma once
#include <math/vector3.h>

struct Camera
{
	float fov = 3.1415f / 2.0f;
	float aspectRatio = 4.0f / 3.0f;
	float zNear = 0.1f;
	float zFar = 100.0f;
	Vector3 position = Vector3();
	Vector3 rotation = Vector3();
};