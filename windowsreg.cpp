#include "windowsreg.h"

WindowsReg::WindowsReg()
{

}

int WindowsReg::get_REG_SZ_value(HKEY _hkey, LPCSTR _lpSubKey, LPCSTR _lpValue){
    // Get Wallpaper Style
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

int WindowsReg::set_REG_SZ_value(HKEY _hkey, LPCSTR _lpSubKey, LPCSTR _lpValue){
    // TODO: Implementar
    // Get Wallpaper Style
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

/*
int WindowsReg::get_DWORD_value(HKEY hkey, LPCSTR lpSubKey, LPCSTR lpValue){

}
*/
