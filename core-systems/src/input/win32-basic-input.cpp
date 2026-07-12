#include "win32-basic-input.h"
#include <cstring>

Win32BasicInput::Win32BasicInput() :
	m_keyStates{},
	m_previouskeyStates{},
	m_mouseButtonStateBitfield(0),
	m_previousMouseButtonStateBitfield(0),
	m_mouseScroll(0)
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

bool Win32BasicInput::IsMouseButtonJustPressed(MouseButton mouseButton) const
{
	return (m_mouseButtonStateBitfield         & (unsigned char)mouseButton) and
	   not (m_previousMouseButtonStateBitfield & (unsigned char)mouseButton);
}

bool Win32BasicInput::IsMouseButtonJustReleased(MouseButton mouseButton) const
{
	return not (m_mouseButtonStateBitfield         & (unsigned char)mouseButton) and
		       (m_previousMouseButtonStateBitfield & (unsigned char)mouseButton);
}

bool Win32BasicInput::IsMouseButtonDown(MouseButton mouseButton) const
{
	return m_mouseButtonStateBitfield & (unsigned char)mouseButton;
}

short Win32BasicInput::GetMouseScroll() const
{
	return m_mouseScroll;
}

void Win32BasicInput::SetKeyState(unsigned char keyCode, bool pressed)
{
	m_keyStates[keyCode] = pressed;
}

void Win32BasicInput::SetMouseButtonState(MouseButton mouseButton, bool pressed)
{
	if (pressed)
		m_mouseButtonStateBitfield |= (unsigned char)mouseButton;
	else
		m_mouseButtonStateBitfield &= ~(unsigned char)mouseButton;
}

void Win32BasicInput::AddMouseScroll(short mouseScroll)
{
	m_mouseScroll += mouseScroll;
}

void Win32BasicInput::Update()
{
	memcpy(m_previouskeyStates, m_keyStates, sizeof(m_keyStates));
	m_previousMouseButtonStateBitfield = m_mouseButtonStateBitfield;
	m_mouseScroll = 0;
}
