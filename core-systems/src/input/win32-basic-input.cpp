#include "win32-basic-input.h"

Win32BasicInput::Win32BasicInput() :
	m_keyStates{}
{

}

bool Win32BasicInput::IsKeyJustPressed(unsigned char keyCode) const
{
	return false;
}

bool Win32BasicInput::IsKeyJustReleased(unsigned char keyCode) const
{
	return false;
}

bool Win32BasicInput::IsKeyDown(unsigned char keyCode) const
{
	return m_keyStates[keyCode];
}

void Win32BasicInput::SetKeyState(unsigned char keyCode, bool pressed)
{
	m_keyStates[keyCode] = pressed;
}
