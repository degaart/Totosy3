#include <Windows.h>
#include <string>
#include <map>
#include <stdexcept>
#include "FlexLayout.h"
#include "Window.h"
#include "Util.h"

class MainWin : public totosy::Window {
public:
    LRESULT onCreate(CREATESTRUCT*);
};

LRESULT MainWin::onCreate(CREATESTRUCT*)
{
    HWND hCtl = CreateWindow(L"BUTTON",
            L"Click me if you dare",
            WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS,
            10, 10,
            175, 48,
            hwnd(),
            (HMENU)101,
            GetModuleHandle(NULL),
            0);
    if(!hCtl)
        throw std::runtime_error("CreateWindow failed");
    return 0;
}

/*
 * Win32 layout guidelines: https://learn.microsoft.com/en-us/windows/win32/uxguide/vis-layout 
 * Win32 dialogs: https://devblogs.microsoft.com/oldnewthing/20050329-00/?p=36043
 */
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, INT nShowCmd)
{
    MainWin mainWindow;
    mainWindow.create("Totosy", 320, 240);
    mainWindow.show(nShowCmd);
    mainWindow.update();

    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

