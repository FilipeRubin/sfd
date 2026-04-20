#pragma once
#include <containers/mesh-data.h>

class IMesh3DGenerator
{
public:
	virtual ~IMesh3DGenerator() = default;
	virtual MeshData GenerateMeshData() const = 0;
};
