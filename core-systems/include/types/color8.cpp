#include "color8.h"
#include "color.h"

Color8::operator Color() const noexcept
{
	return Color(
		float(r) / 255.0f,
		float(g) / 255.0f,
		float(b) / 255.0f,
		float(a) / 255.0f
	);
}
