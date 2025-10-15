#include "win32-window.h"
#include <Windows.h>

unsigned int Win32Window::s_instanceCount = 0U;
Win32WindowClass Win32Window::s_windowClass = Win32WindowClass();

void Win32Window::Finalize()
{
    DestroyWindow((HWND)m_hwnd);
    Decrement();
}

void Win32Window::Process()
{
    MSG msg = {};
    while (PeekMessage(&msg, (HWND)m_hwnd, NULL, NULL, PM_REMOVE) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

bool Win32Window::ShouldClose() const
{
    return m_shouldClose;
}

bool Win32Window::IsInitialized() const
{
    return m_hwnd != nullptr;
}

bool Win32Window::TryInitialize(const WindowParameters& parameters)
{
    if (not TryIncrement())
    {
        return false;
    }
    
    HINSTANCE hInstance = (HINSTANCE)s_windowClass.GetInstanceHandle();

    SetProcessDPIAware();

    m_hwnd = CreateWindowEx(
        0,
        s_windowClass.GetWindowClassName(),
        parameters.title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        parameters.width,
        parameters.height,
        NULL,
        NULL,
        hInstance,
        NULL
    );
        
    if (m_hwnd == NULL)
    {
        DWORD err = GetLastError();
        Decrement();
        return false;
    }

    SetWindowLongPtr((HWND)m_hwnd, GWLP_USERDATA, (LONG_PTR)this);

    ShowWindow((HWND)m_hwnd, SW_SHOW);

    return true;
}

void Win32Window::Close()
{
    m_shouldClose = true;
}

bool Win32Window::TryIncrement()
{
    if (s_instanceCount == 0U)
    {
        if (not s_windowClass.TryRegister(L"SFDWND"))
        {
            return false;
        }
    }
    s_instanceCount++;
    return true;
}

void Win32Window::Decrement()
{
    s_instanceCount--;
    if (s_instanceCount == 0U)
    {
        s_windowClass.Unregister();
    }
}
