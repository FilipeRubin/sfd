#pragma once
#include <types/color8.h>
#include <types/dimensions.h>

class TextureData
{
public:
	TextureData();
	TextureData(const TextureData& other) = delete;
	TextureData(TextureData&& other) noexcept;
	~TextureData();
	TextureData& operator=(const TextureData& other) = delete;
	TextureData& operator=(TextureData&& other) noexcept;
	const Color8* GetData() const;
	size_t GetDataSize() const;
	const Dimensions& GetDimensions() const;
	void SetData(const Color8* const data, const Dimensions& dimensions);
	void SetEmptyData(const Dimensions& dimensions);
	Color8& Pixel(const Dimensions& index);
private:
	Color8* m_data;
	Dimensions m_dimensions;
};
