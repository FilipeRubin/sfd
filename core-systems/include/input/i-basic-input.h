#pragma once

class IBasicInput
{
public:
	virtual ~IBasicInput() = default;
	virtual bool IsKeyJustPressed(unsigned char keyCode) const = 0;
	virtual bool IsKeyJustReleased(unsigned char keyCode) const = 0;
	virtual bool IsKeyDown(unsigned char keyCode) const = 0;
};