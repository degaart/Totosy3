#include "Window.h"
#include "Util.h"
#include <stdexcept>
#include <sstream>

namespace totosy {

std::map<HWND, Window*> Window::_windowMap;
unsigned Window::_nextClassID = 0;

Window::Window()
    : _hWnd(NULL)
{
    InterlockedIncrement(&_nextClassID);

    std::wstringstream ss;
    ss << "Window#" << std::hex << _nextClassID;
    _className = ss.str();

    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(wc);
    wc.style = CS_VREDRAW|CS_HREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
    wc.lpszClassName = _className.c_str();
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    if(!RegisterClassEx(&wc))
        throw std::runtime_error("RegisterClassEx failed");
}

Window::~Window()
{
    if(!_hWnd) {
        _windowMap.erase(_hWnd);
        DestroyWindow(_hWnd);
    }
    UnregisterClass(_className.c_str(), GetModuleHandle(NULL));
}

HWND Window::hwnd() const
{
    return _hWnd;
}

void Window::create(const std::string& caption, int w, int h)
{
    if(_hWnd) {
        return;
    }

    unsigned exStyle = 0;
    unsigned style = WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN;
    if(w != -1 && h != -1) {
        RECT rc = { 0, 0, w, h };
        AdjustWindowRectEx(&rc, style, FALSE, exStyle);
        w = rc.right - rc.left;
        h = rc.bottom - rc.top;
    }

    _hWnd = CreateWindow(_className.c_str(),
                 toWideChar(caption).c_str(),
                 WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN,
                 CW_USEDEFAULT, CW_USEDEFAULT,
                 w, h,
                 NULL,
                 NULL,
                 GetModuleHandle(NULL),
                 this);
    if(!_hWnd)
        throw std::runtime_error("CreateWindow failed");
}

void Window::show(int nShowCmd)
{
    if(_hWnd) {
        ShowWindow(_hWnd, nShowCmd);
    }
}

void Window::update()
{
    if(_hWnd) {
        UpdateWindow(_hWnd);
    }
}

void Window::destroy()
{
    if(_hWnd) {
        DestroyWindow(_hWnd);
    }
    _hWnd = NULL;
}

LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    if(msg == WM_NCCREATE) {
        CREATESTRUCT* createStruct = (CREATESTRUCT*)lparam;
        Window* window = (Window*)createStruct->lpCreateParams;
        window->_hWnd = hwnd;
        _windowMap[hwnd] = window;
    } else {
        std::map<HWND, Window*>::iterator it = _windowMap.find(hwnd);
        if(it != _windowMap.end()) {
            return it->second->WindowProc(msg, wparam, lparam);
        }
    }
    return DefWindowProc(hwnd, msg, wparam, lparam);
}

LRESULT Window::WindowProc(UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch(msg) {
        case WM_CREATE:
            return onCreate((CREATESTRUCT*)lparam);
        case WM_DESTROY:
            return onDestroy();
        case WM_CLOSE:
            return onClose();
        default:
            return DefWindowProc(_hWnd, msg, wparam, lparam);
    }
}

LRESULT Window::onCreate(CREATESTRUCT* cs)
{
    return DefWindowProc(_hWnd, WM_CREATE, 0, (LPARAM)cs);
}

LRESULT Window::onDestroy()
{
    PostQuitMessage(0);
    return 0;
}

LRESULT Window::onClose()
{
    destroy();
    return 0;
}

} // namespace totosy

