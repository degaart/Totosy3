#pragma once

#include <Windows.h>
#include <string>
#include <map>

namespace totosy {

    class Window {
        public:
            Window();
            virtual ~Window();
            void create(const std::string& caption, int w = -1, int h = -1);
            void show(int nShowCmd);
            void update();
            HWND hwnd() const;
            void destroy();
        private:
            static std::map<HWND, Window*> _windowMap;
            static unsigned _nextClassID;
            HWND _hWnd;
            std::wstring _className;

            static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
        protected:
            virtual LRESULT WindowProc(UINT msg, WPARAM wparam, LPARAM lparam);
            virtual LRESULT onCreate(CREATESTRUCT*);
            virtual LRESULT onDestroy();
            virtual LRESULT onClose();
    };

} // namespace totosy

