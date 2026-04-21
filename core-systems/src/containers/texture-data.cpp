#include <containers/texture-data.h>
#include <cstring>

TextureData::TextureData() :
	m_data(nullptr),
	m_dimensions(Dimensions(0, 0))
{
}

TextureData::TextureData(TextureData&& other) noexcept :
	m_data(other.m_data),
	m_dimensions(other.m_dimensions)
{
	other.m_data = nullptr;
	other.m_dimensions = Dimensions(0, 0);
}

TextureData::~TextureData()
{
	delete[] m_data;
}

TextureData& TextureData::operator=(TextureData&& other) noexcept
{
	if (this != &other)
	{
		delete[] m_data;

		m_data = other.m_data;
		m_dimensions = other.m_dimensions;

		other.m_data = nullptr;
		other.m_dimensions = Dimensions(0, 0);
	}

	return *this;
}

const Color8* TextureData::GetData() const
{
	return m_data;
}

size_t TextureData::GetDataSize() const
{
	return size_t(m_dimensions.width * m_dimensions.height) * sizeof(Color8);
}

const Dimensions& TextureData::GetDimensions() const
{
	return m_dimensions;
}

void TextureData::SetData(const Color8* const data, const Dimensions& dimensions)
{
	delete[] m_data;

	size_t pixelCount = size_t(dimensions.width) * size_t(dimensions.height);
	m_data = new Color8[pixelCount];
	size_t dataSize = size_t(dimensions.width) * size_t(dimensions.height) * sizeof(Color8);
	std::memcpy(m_data, data, dataSize);
	m_dimensions = dimensions;
}

void TextureData::SetEmptyData(const Dimensions& dimensions)
{
	delete[] m_data;

	size_t pixelCount = size_t(dimensions.width) * size_t(dimensions.height);
	m_data = new Color8[pixelCount];
	m_dimensions = dimensions;
}

Color8& TextureData::Pixel(const Dimensions& index)
{
	return m_data[index.height * m_dimensions.width + index.width];
}
