#include <rendering/data-generation/texture-2d/raw-data-texture-2d-generator.h>
#include <cstring>

RawDataTexture2DGenerator::RawDataTexture2DGenerator(Color8* data, const Dimensions& dimensions) :
    m_data(new Color8[dimensions.x * dimensions.y]),
    m_dimensions(dimensions)
{
    size_t dataLength = size_t(dimensions.x) * size_t(dimensions.y) * sizeof(Color8);
    std::memcpy(m_data, data, dataLength);
}

RawDataTexture2DGenerator::~RawDataTexture2DGenerator()
{
    delete[] m_data;
}

TextureData RawDataTexture2DGenerator::GenerateTextureData() const
{
    TextureData data;
    data.SetData(m_data, m_dimensions);
    return data;
}
