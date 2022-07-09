#include "windowsreg.h"
#include <stdio.h>

WindowsReg::WindowsReg()
{

}

int WindowsReg::get_REG_SZ_value(HKEY _hkey, LPCSTR _lpSubKey, LPCSTR _lpValue){
    // Get REG_SZ type Registry
    HKEY hkey = _hkey;
    LPCSTR lpSubKey = _lpSubKey;
    LPCSTR lpValue = _lpValue;
    DWORD dwFlags = RRF_RT_REG_SZ;
    LPDWORD pdwType = nullptr;
    DWORD val;
    DWORD dataSize = sizeof(val);

    int result = RegGetValueA(hkey, lpSubKey, lpValue, dwFlags, pdwType, &val, &dataSize);

    if (ERROR_SUCCESS == result) {
        return val - 48;
    } else {
        return result;
    }
}

int WindowsReg::set_REG_SZ_value(HKEY _hKey, LPCSTR _lpValueName, const BYTE *_lpData){
    // Set REG_SZ type Registry
    HKEY hKey = _hKey;
    LPCSTR lpValueName = _lpValueName;
    DWORD dwType = RRF_RT_REG_SZ;
    DWORD cbData = sizeof(_lpData);

    int result = RegSetValueExA(hKey, lpValueName, 0, dwType, _lpData, cbData);

    if (ERROR_SUCCESS == result) {
        return 0;
    } else {
        return result;
    }
}

int WindowsReg::get_DWORD_value(HKEY _hkey, LPCSTR _lpSubKey, LPCSTR _lpValue){
    // Get DWORD type Registry
    HKEY hkey = _hkey;
    LPCSTR lpSubKey = _lpSubKey;
    LPCSTR lpValue = _lpValue;
    DWORD dwFlags = RRF_RT_DWORD;
    LPDWORD pdwType = nullptr;
    DWORD val;
    DWORD dataSize = sizeof(val);

    int result = RegGetValueA(hkey, lpSubKey, lpValue, dwFlags, pdwType, &val, &dataSize);

    if (ERROR_SUCCESS == result) {
        return val;
    } else {
        return result;
    }
}
