#pragma once

#include <string>

namespace totosy {
    std::wstring toWideChar(const char* s, int len = -1);
    std::wstring toWideChar(const std::string& s);
    std::string toUTF8(const wchar_t* s, int len = -1);
    std::string toUTF8(const std::wstring& s);
}

