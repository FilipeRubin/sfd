#include <rendering/data-generation/texture-2d/raw-data-texture-2d-generator.h>
#include <cstring>

RawDataTexture2DGenerator::RawDataTexture2DGenerator(Shared<FixedArray<Color8>> data, const Dimensions& dimensions) :
    m_data(data),
    m_dimensions(dimensions)
{
}

TextureData RawDataTexture2DGenerator::GenerateTextureData() const
{
    TextureData data;
    data.SetData(m_data, m_dimensions);
    return data;
}
