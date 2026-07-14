#include "win32-window-class.h"
#include "win32-window.h"
#include "input/win32-basic-input.h"
#include <Windows.h>

static inline LRESULT ProcessMouseButtonMessage(const UINT& msg, const WPARAM& wParam, Win32BasicInput& input);

#include <iostream>
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
	case WM_SIZE:
	{
		Win32Window* window = (Win32Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		int width = (int)LOWORD(lParam);
		int height = (int)HIWORD(lParam);
		window->UpdateSize({ width, height });
		if (window->GetWindowSizeCallback())
			window->GetWindowSizeCallback()({ width, height });
		return 0;
	}
	case WM_KEYDOWN:
	{
		Win32Window* window = (Win32Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		Win32BasicInput* basicInput = (Win32BasicInput*)window->GetBasicInput();
		unsigned char key = unsigned char(wParam);
		bool repeating = (lParam & (1 << 30)) != 0;
		if (not repeating)
		{
			basicInput->SetKeyState(key, true);
		}
		return 0;
	}
	case WM_KEYUP:
	{
		Win32Window* window = (Win32Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		Win32BasicInput* basicInput = (Win32BasicInput*)window->GetBasicInput();
		unsigned char key = unsigned char(wParam);
		basicInput->SetKeyState(key, false);
		return 0;
	}
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	case WM_MOUSEWHEEL:
	{
		Win32Window* window = (Win32Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		Win32BasicInput* basicInput = (Win32BasicInput*)window->GetBasicInput();
		return ProcessMouseButtonMessage(msg, wParam, *basicInput);
	}
	case WM_MOUSEMOVE:
	{
		WORD x = LOWORD(lParam);
		WORD y = HIWORD(lParam);
		Win32Window* window = (Win32Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		Win32BasicInput* basicInput = (Win32BasicInput*)window->GetBasicInput();
		basicInput->UpdateMousePosition({ (float)x, (float)y });
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

LRESULT ProcessMouseButtonMessage(const UINT& msg, const WPARAM& wParam, Win32BasicInput& input)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
		input.SetMouseButtonState((MouseButton)MK_LBUTTON, true);
		break;
	case WM_LBUTTONUP:
		input.SetMouseButtonState((MouseButton)MK_LBUTTON, false);
		break;
	case WM_MBUTTONDOWN:
		input.SetMouseButtonState((MouseButton)MK_MBUTTON, true);
		break;
	case WM_MBUTTONUP:
		input.SetMouseButtonState((MouseButton)MK_MBUTTON, false);
		break;
	case WM_RBUTTONDOWN:
		input.SetMouseButtonState((MouseButton)MK_RBUTTON, true);
		break;
	case WM_RBUTTONUP:
		input.SetMouseButtonState((MouseButton)MK_RBUTTON, false);
		break;
	case WM_XBUTTONDOWN:
	{
		WORD button = HIWORD(wParam);
		if (button == XBUTTON1) input.SetMouseButtonState((MouseButton)MK_XBUTTON1, true);
		else if (button == XBUTTON2) input.SetMouseButtonState((MouseButton)MK_XBUTTON2, true);
		break;
	}
	case WM_XBUTTONUP:
	{
		WORD button = HIWORD(wParam);
		if (button == XBUTTON1) input.SetMouseButtonState((MouseButton)MK_XBUTTON1, false);
		else if (button == XBUTTON2) input.SetMouseButtonState((MouseButton)MK_XBUTTON2, false);
		break;
	}
	case WM_MOUSEWHEEL:
	{
		short wheelDelta = GET_WHEEL_DELTA_WPARAM(wParam);
		short mouseScroll = wheelDelta > 0 ? 1 : -1;
		input.AddMouseScroll(mouseScroll);
		break;
	}
	}
	return 0;
}
