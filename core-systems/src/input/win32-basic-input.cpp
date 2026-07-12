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

bool Win32BasicInput::IsKeyJustPressed(KeyboardKey key) const
{
	return m_keyStates[(unsigned char)key] == true and m_previouskeyStates[(unsigned char)key] == false;
}

bool Win32BasicInput::IsKeyJustReleased(KeyboardKey key) const
{
	return m_keyStates[(unsigned char)key] == false and m_previouskeyStates[(unsigned char)key] == true;
}

bool Win32BasicInput::IsKeyDown(KeyboardKey key) const
{
	return m_keyStates[(unsigned char)key];
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
