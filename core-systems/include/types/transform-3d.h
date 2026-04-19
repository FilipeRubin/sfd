#pragma once
#include <math/vector3.h>

struct Transform3D
{
	Vector3 position = Vector3();
	Vector3 rotation = Vector3();
	Vector3 scale = Vector3(1.0f, 1.0f, 1.0f);
};
