#ifndef WINDOWSREG_H
#define WINDOWSREG_H

#include <windows.h>

class WindowsReg
{
public:
    WindowsReg();

    static int get_REG_SZ_value(HKEY hkey, LPCSTR lpSubKey, LPCSTR lpValue);
    static int set_REG_SZ_value(HKEY hKey, LPCSTR lpValueName, DWORD data);
    static int get_DWORD_value(HKEY hkey, LPCSTR lpSubKey, LPCSTR lpValue);
    static int set_DWORD_value(HKEY hKey, LPCSTR lpValueName, DWORD data);
};

#endif // WINDOWSREG_H
