#include <rendering/data-generation/mesh-3d/plane-mesh-3d-generator.h>

PlaneMesh3DGenerator::PlaneMesh3DGenerator(Vector2 dimensions) :
	m_dimensions(dimensions)
{
}

MeshData PlaneMesh3DGenerator::GenerateMeshData() const
{
	Vertex3D vertices[]
	{
		{ {  m_dimensions.x / 2.0f, 0.0f,  m_dimensions.y / 2.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } },
		{ {  m_dimensions.x / 2.0f, 0.0f, -m_dimensions.y / 2.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f } },
		{ { -m_dimensions.x / 2.0f, 0.0f, -m_dimensions.y / 2.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f } },
		{ { -m_dimensions.x / 2.0f, 0.0f,  m_dimensions.y / 2.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f } }
	};

	unsigned int indices[]
	{
		0U, 1U, 2U,
		0U, 2U, 3U
	};

	MeshData data;
	data.SetVertices(vertices, 4ULL);
	data.SetIndices(indices, 6ULL);
	return data;
}
