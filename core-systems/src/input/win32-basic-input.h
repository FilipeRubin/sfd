#pragma once
#include <input/i-basic-input.h>

class Win32BasicInput final : public IBasicInput
{
public:
	Win32BasicInput();
	bool IsKeyJustPressed(unsigned char keyCode) const override;
	bool IsKeyJustReleased(unsigned char keyCode) const override;
	bool IsKeyDown(unsigned char keyCode) const override;
	void SetKeyState(unsigned char keyCode, bool pressed);
private:
	bool m_keyStates[256];
};
