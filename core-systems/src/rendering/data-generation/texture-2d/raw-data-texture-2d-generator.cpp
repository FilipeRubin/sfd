#include <rendering/data-generation/texture-2d/raw-data-texture-2d-generator.h>
#include <cstring>

RawDataTexture2DGenerator::RawDataTexture2DGenerator(Color8* data, const Dimensions& dimensions) :
    m_data(new Color8[dimensions.width * dimensions.height]),
    m_dimensions(dimensions)
{
    size_t dataSize = size_t(dimensions.width) * size_t(dimensions.height) * sizeof(Color8);
    std::memcpy(m_data, data, dataSize);
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
