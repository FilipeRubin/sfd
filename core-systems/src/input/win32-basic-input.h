#pragma once
#include <input/i-basic-input.h>

class Win32BasicInput final : public IBasicInput
{
public:
	Win32BasicInput();
	bool IsKeyJustPressed(KeyboardKey key) const override;
	bool IsKeyJustReleased(KeyboardKey key) const override;
	bool IsKeyDown(KeyboardKey key) const override;
	bool IsMouseButtonJustPressed(MouseButton mouseButton) const override;
	bool IsMouseButtonJustReleased(MouseButton mouseButton) const override;
	bool IsMouseButtonDown(MouseButton mouseButton) const override;
	short GetMouseScroll() const override;
	void SetKeyState(unsigned char keyCode, bool pressed);
	void SetMouseButtonState(MouseButton mouseButton, bool pressed);
	void AddMouseScroll(short mouseScroll);
	void Update();
private:
	bool m_keyStates[256];
	bool m_previouskeyStates[256];
	unsigned char m_mouseButtonStateBitfield;
	unsigned char m_previousMouseButtonStateBitfield;
	short m_mouseScroll;
};
