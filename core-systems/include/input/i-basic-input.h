#pragma once
#include "keyboard-key.h"
#include "mouse-button.h"

class IBasicInput
{
public:
	virtual ~IBasicInput() = default;
	virtual bool IsKeyJustPressed(KeyboardKey key) const = 0;
	virtual bool IsKeyJustReleased(KeyboardKey key) const = 0;
	virtual bool IsKeyDown(KeyboardKey key) const = 0;
	virtual bool IsMouseButtonJustPressed(MouseButton mouseButton) const = 0;
	virtual bool IsMouseButtonJustReleased(MouseButton mouseButton) const = 0;
	virtual bool IsMouseButtonDown(MouseButton mouseButton) const = 0;
	virtual short GetMouseScroll() const = 0;
};
