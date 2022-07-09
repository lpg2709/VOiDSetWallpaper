#ifndef WINDOWSREG_H
#define WINDOWSREG_H

#include <windows.h>

class WindowsReg
{
public:
    WindowsReg();

    static int get_REG_SZ_value(HKEY hkey, LPCSTR lpSubKey, LPCSTR lpValue);
    static int set_REG_SZ_value(HKEY _hKey, LPCSTR _lpValueName, const BYTE *_lpData);
    static int get_DWORD_value(HKEY hkey, LPCSTR lpSubKey, LPCSTR lpValue);
};

#endif // WINDOWSREG_H
