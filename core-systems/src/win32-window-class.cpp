#include "win32-window-class.h"
#include "win32-window.h"
#include <Windows.h>

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
	{
		Win32Window* window = (Win32Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->Close();
		return 0;
	}
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

void* Win32WindowClass::GetInstanceHandle() const
{
	return m_hInstance;
}

const wchar_t* Win32WindowClass::GetWindowClassName() const
{
	return m_className;
}

bool Win32WindowClass::IsActive() const
{
	return m_className != nullptr;
}

bool Win32WindowClass::TryRegister(const wchar_t* className)
{
	m_hInstance = GetModuleHandle(NULL);
	if (m_hInstance == NULL)
		return false;
	HINSTANCE hInstance = (HINSTANCE)m_hInstance;
	m_className = className;

	WNDCLASSEX wc = {
		.cbSize = sizeof(WNDCLASSEX),
		.style = CS_OWNDC,
		.lpfnWndProc = WndProc,
		.cbClsExtra = 0,
		.cbWndExtra = 0,
		.hInstance = hInstance,
		.hIcon = LoadIcon(NULL, IDI_APPLICATION),
		.hCursor = LoadCursor(NULL, IDC_ARROW),
		.hbrBackground = NULL,
		.lpszMenuName = NULL,
		.lpszClassName = m_className,
		.hIconSm = NULL
	};

	ATOM classId = RegisterClassEx(&wc);
	if (classId == NULL)
		return false;

	return true;
}

void Win32WindowClass::Unregister()
{
	UnregisterClass(m_className, (HINSTANCE)m_hInstance);
	m_hInstance = nullptr;
	m_className = nullptr;
}