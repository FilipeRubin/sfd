#include <rendering/data-generation/mesh-3d/terrain-mesh-3d-generator.h>

TerrainMesh3DGenerator::TerrainMesh3DGenerator(const Dimensions& gridSize, Shared<FixedArray<float>> heightMapData) :
    m_gridSize(gridSize),
    m_heightMapData(heightMapData)
{
}

MeshData TerrainMesh3DGenerator::GenerateMeshData() const
{
    MeshData result;
    size_t verticesCount = (size_t)m_gridSize.width * (size_t)m_gridSize.height;

    Shared<FixedArray<Vertex3D>> vertices = Shared<FixedArray<Vertex3D>>(new FixedArray<Vertex3D>(verticesCount));
    for (size_t i = 0ULL; i < verticesCount; i++)
    {
        int x = i % m_gridSize.width;
        int y = i / m_gridSize.width;

        (*vertices)[i].position.x = (float)x / (float)(m_gridSize.width - 1);
        (*vertices)[i].position.y = (*m_heightMapData)[i];
        (*vertices)[i].position.z = (float)y / (float)(m_gridSize.height - 1);

        // It's a fixed value for now. Will change later.
        (*vertices)[i].normal.x = 0.0f;
        (*vertices)[i].normal.y = 1.0f;
        (*vertices)[i].normal.z = 0.0f;

        (*vertices)[i].uv.x = (float)x;
        (*vertices)[i].uv.y = float(m_gridSize.height - y);
    }

    size_t indicesCount = 6ULL * size_t(m_gridSize.width - 1) * size_t(m_gridSize.height - 1);
    Shared<FixedArray<unsigned int>> indices = Shared<FixedArray<unsigned int>>(new FixedArray<unsigned int>(indicesCount));
    {
        for (int y = 0; y < m_gridSize.height - 1; y++)
        {
            for (int x = 0; x < m_gridSize.width - 1; x++)
            {
                //
                //  v1------v2
                //   |\     |
                //   | \    |
                //   |  \   |
                //   |   \  |
                //   |    \ |
                //   |     \|
                //  v3------v4
                //

                const int v1 = y * m_gridSize.width + x;
                const int v2 = y * m_gridSize.width + x + 1;
                const int v3 = (y + 1) * m_gridSize.width + x;
                const int v4 = (y + 1) * m_gridSize.width + x + 1;

                const size_t i = size_t(x + (m_gridSize.width - 1) * y) * 6ULL;

                (*indices)[i + 0] = v3;
                (*indices)[i + 1] = v4;
                (*indices)[i + 2] = v1;

                (*indices)[i + 3] = v4;
                (*indices)[i + 4] = v2;
                (*indices)[i + 5] = v1;
            }
        }
    }

    result.SetVertices(vertices);
    result.SetIndices(indices);

    return result;
}
