#ifndef WINDOWSREG_H
#define WINDOWSREG_H

#include <windows.h>
#include <QString>
#include <QStringList>

class WindowsReg
{
public:
    WindowsReg();

    static int get_REG_SZ_value(HKEY hkey, LPCSTR lpSubKey, LPCSTR lpValue);
    static int set_REG_SZ_value(HKEY _hKey, LPCSTR strSubKey, LPCSTR lpVal, DWORD _lpData);
    static int get_DWORD_value(HKEY hkey, LPCSTR lpSubKey, LPCSTR lpValue);
    static int set_DWORD_value(HKEY _hKey, LPCSTR strSubKey, LPCSTR lpVal, DWORD _lpData);
};

#endif // WINDOWSREG_H
