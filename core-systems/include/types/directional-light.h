#pragma once
#include "color.h"
#include <math/vector3.h>

struct DirectionalLight
{
	Color ambient;
	Color diffuse;
	Vector3 direction;
};