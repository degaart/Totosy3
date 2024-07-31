#include "Windows.h"
#include "Util.h"
#include <vector>
#include <stdexcept>

namespace totosy {

std::wstring toWideChar(const char* s, int len)
{
    int size = MultiByteToWideChar(CP_UTF8,
            0,
            s,
            len,
            NULL,
            0);
    if(size == 0)
        throw std::runtime_error("MultiByteToWideChar failed");
    std::vector<wchar_t> buffer(size);
    int ret = MultiByteToWideChar(CP_UTF8,
            0,
            s,
            len,
            &buffer[0],
            size);
    if(ret == 0)
        throw std::runtime_error("MultiByteToWideChar failed");

    std::wstring result(&buffer[0], size);
    return result;
}

std::wstring toWideChar(const std::string& s)
{
    return toWideChar(s.c_str(), s.size());
}

std::string toUTF8(const wchar_t* s, int len)
{
    int size = WideCharToMultiByte(CP_UTF8,
            0,
            s, len,
            NULL, 0,
            NULL,
            NULL);
    if(size == 0)
        throw std::runtime_error("WideCharToMultiByte failed");

    std::vector<char> buffer(size);
    int ret = WideCharToMultiByte(CP_UTF8,
            0,
            s, len,
            &buffer[0], size,
            NULL,
            NULL);
    if(ret == 0)
        throw std::runtime_error("WideCharToMultiByte failed");

    return std::string(&buffer[0], size - 1);
}

std::string toUTF8(const std::wstring& s)
{
    return toUTF8(s.c_str(), s.size());
}

} // namespace totosy

