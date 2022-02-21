#define _CRT_SECURE_NO_WARNINGS
#include "sundry.h"
wstring s_to_ws(string& s)
{
    setlocale(LC_ALL, "chs");
    const char* temp = s.c_str();
    int l = s.size() + 1;
    wchar_t* dest = new wchar_t[l];
    wmemset(dest, 0, l);
    mbstowcs(dest, temp, l);
    wstring result = dest;
    delete[]dest;
    setlocale(LC_ALL, "C");
    return result;
}
