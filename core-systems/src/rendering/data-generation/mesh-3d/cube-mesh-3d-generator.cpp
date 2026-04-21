#include <rendering/data-generation/mesh-3d/cube-mesh-3d-generator.h>

CubeMesh3DGenerator::CubeMesh3DGenerator(const Vector3& dimensions) :
	m_dimensions(dimensions)
{
}

MeshData CubeMesh3DGenerator::GenerateMeshData() const
{
	Vertex3D vertices[]
	{
		// Front (+Z)
		{ { -m_dimensions.x / 2.0f, -m_dimensions.y / 2.0f,  m_dimensions.z  / 2.0f }, {  0.0f,  0.0f,  1.0f }, { 0.0f, 0.0f } },
		{ {  m_dimensions.x / 2.0f, -m_dimensions.y / 2.0f,  m_dimensions.z  / 2.0f }, {  0.0f,  0.0f,  1.0f }, { 1.0f, 0.0f } },
		{ {  m_dimensions.x / 2.0f,  m_dimensions.y / 2.0f,  m_dimensions.z  / 2.0f }, {  0.0f,  0.0f,  1.0f }, { 1.0f, 1.0f } },
		{ { -m_dimensions.x / 2.0f,  m_dimensions.y / 2.0f,  m_dimensions.z  / 2.0f }, {  0.0f,  0.0f,  1.0f }, { 0.0f, 1.0f } },

		// Back (-Z)
		{ {  m_dimensions.x / 2.0f, -m_dimensions.y / 2.0f, -m_dimensions.z  / 2.0f }, {  0.0f,  0.0f, -1.0f }, { 0.0f, 0.0f } },
		{ { -m_dimensions.x / 2.0f, -m_dimensions.y / 2.0f, -m_dimensions.z  / 2.0f }, {  0.0f,  0.0f, -1.0f }, { 1.0f, 0.0f } },
		{ { -m_dimensions.x / 2.0f,  m_dimensions.y / 2.0f, -m_dimensions.z  / 2.0f }, {  0.0f,  0.0f, -1.0f }, { 1.0f, 1.0f } },
		{ {  m_dimensions.x / 2.0f,  m_dimensions.y / 2.0f, -m_dimensions.z  / 2.0f }, {  0.0f,  0.0f, -1.0f }, { 0.0f, 1.0f } },

		// Left (-X)
		{ { -m_dimensions.x / 2.0f, -m_dimensions.y / 2.0f, -m_dimensions.z  / 2.0f }, { -1.0f,  0.0f,  0.0f }, { 0.0f, 0.0f } },
		{ { -m_dimensions.x / 2.0f, -m_dimensions.y / 2.0f,  m_dimensions.z  / 2.0f }, { -1.0f,  0.0f,  0.0f }, { 1.0f, 0.0f } },
		{ { -m_dimensions.x / 2.0f,  m_dimensions.y / 2.0f,  m_dimensions.z  / 2.0f }, { -1.0f,  0.0f,  0.0f }, { 1.0f, 1.0f } },
		{ { -m_dimensions.x / 2.0f,  m_dimensions.y / 2.0f, -m_dimensions.z  / 2.0f }, { -1.0f,  0.0f,  0.0f }, { 0.0f, 1.0f } },

		// Right (+X)
		{ {  m_dimensions.x / 2.0f, -m_dimensions.y / 2.0f,  m_dimensions.z  / 2.0f }, {  1.0f,  0.0f,  0.0f }, { 0.0f, 0.0f } },
		{ {  m_dimensions.x / 2.0f, -m_dimensions.y / 2.0f, -m_dimensions.z  / 2.0f }, {  1.0f,  0.0f,  0.0f }, { 1.0f, 0.0f } },
		{ {  m_dimensions.x / 2.0f,  m_dimensions.y / 2.0f, -m_dimensions.z  / 2.0f }, {  1.0f,  0.0f,  0.0f }, { 1.0f, 1.0f } },
		{ {  m_dimensions.x / 2.0f,  m_dimensions.y / 2.0f,  m_dimensions.z  / 2.0f }, {  1.0f,  0.0f,  0.0f }, { 0.0f, 1.0f } },

		// Top (+Y)
		{ { -m_dimensions.x / 2.0f,  m_dimensions.y / 2.0f,  m_dimensions.z  / 2.0f }, {  0.0f,  1.0f,  0.0f }, { 0.0f, 0.0f } },
		{ {  m_dimensions.x / 2.0f,  m_dimensions.y / 2.0f,  m_dimensions.z  / 2.0f }, {  0.0f,  1.0f,  0.0f }, { 1.0f, 0.0f } },
		{ {  m_dimensions.x / 2.0f,  m_dimensions.y / 2.0f, -m_dimensions.z  / 2.0f }, {  0.0f,  1.0f,  0.0f }, { 1.0f, 1.0f } },
		{ { -m_dimensions.x / 2.0f,  m_dimensions.y / 2.0f, -m_dimensions.z  / 2.0f }, {  0.0f,  1.0f,  0.0f }, { 0.0f, 1.0f } },

		// Bottom (-Y)
		{ { -m_dimensions.x / 2.0f, -m_dimensions.y / 2.0f, -m_dimensions.z  / 2.0f }, {  0.0f, -1.0f,  0.0f }, { 0.0f, 0.0f } },
		{ {  m_dimensions.x / 2.0f, -m_dimensions.y / 2.0f, -m_dimensions.z  / 2.0f }, {  0.0f, -1.0f,  0.0f }, { 1.0f, 0.0f } },
		{ {  m_dimensions.x / 2.0f, -m_dimensions.y / 2.0f,  m_dimensions.z  / 2.0f }, {  0.0f, -1.0f,  0.0f }, { 1.0f, 1.0f } },
		{ { -m_dimensions.x / 2.0f, -m_dimensions.y / 2.0f,  m_dimensions.z  / 2.0f }, {  0.0f, -1.0f,  0.0f }, { 0.0f, 1.0f } }
	};

	unsigned int indices[]
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

		// Bottom (-Y)
		20, 21, 22,
		22, 23, 20,

		// Top (+Y)
		16, 17, 18,
		18, 19, 16
	};

	MeshData data;
	data.SetVertices(vertices, 24ULL);
	data.SetIndices(indices, 36ULL);
	return data;
}
