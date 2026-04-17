#include "color.h"
#include "color8.h"
#include <algorithm>

Color::operator Color8() const noexcept
{
	return Color8(
		unsigned char(std::clamp(r, 0.0f, 1.0f) * 255.0f + 0.5f),
		unsigned char(std::clamp(g, 0.0f, 1.0f) * 255.0f + 0.5f),
		unsigned char(std::clamp(b, 0.0f, 1.0f) * 255.0f + 0.5f),
		unsigned char(std::clamp(a, 0.0f, 1.0f) * 255.0f + 0.5f)
	);
}
