#pragma once
#include "mouse-button.h"

class IBasicInput
{
public:
	virtual ~IBasicInput() = default;
	virtual bool IsKeyJustPressed(unsigned char keyCode) const = 0;
	virtual bool IsKeyJustReleased(unsigned char keyCode) const = 0;
	virtual bool IsKeyDown(unsigned char keyCode) const = 0;
	virtual bool IsMouseButtonJustPressed(MouseButton mouseButton) const = 0;
	virtual bool IsMouseButtonJustReleased(MouseButton mouseButton) const = 0;
	virtual bool IsMouseButtonDown(MouseButton mouseButton) const = 0;
	virtual short GetMouseScroll() const = 0;
};
