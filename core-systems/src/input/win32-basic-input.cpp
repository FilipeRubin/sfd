#include "win32-basic-input.h"
#include <cstring>

Win32BasicInput::Win32BasicInput() :
	m_keyStates{},
	m_previouskeyStates{}
{

}

bool Win32BasicInput::IsKeyJustPressed(unsigned char keyCode) const
{
	return m_keyStates[keyCode] == true and m_previouskeyStates[keyCode] == false;
}

bool Win32BasicInput::IsKeyJustReleased(unsigned char keyCode) const
{
	return m_keyStates[keyCode] == false and m_previouskeyStates[keyCode] == true;
}

bool Win32BasicInput::IsKeyDown(unsigned char keyCode) const
{
	return m_keyStates[keyCode];
}

void Win32BasicInput::SetKeyState(unsigned char keyCode, bool pressed)
{
	m_keyStates[keyCode] = pressed;
}

void Win32BasicInput::Update()
{
	memcpy(m_previouskeyStates, m_keyStates, sizeof(m_keyStates));
}
