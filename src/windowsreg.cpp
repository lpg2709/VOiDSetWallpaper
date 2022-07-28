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

int WindowsReg::set_REG_SZ_value(HKEY _hKey, LPCSTR strSubKey, LPCSTR lpVal, DWORD _lpData){
    HKEY hKey_handler;
    QString data =  QString::number(_lpData) + "\0";

    LSTATUS lError = RegOpenKeyExA(_hKey, strSubKey, 0, KEY_ALL_ACCESS, &hKey_handler);
    if(ERROR_FILE_NOT_FOUND == lError) {
        lError = RegCreateKeyExA(_hKey, strSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey_handler, NULL);
    }

    if (ERROR_SUCCESS == lError) {
        printf("A: %s, %d\n", data.toStdString().c_str(),  sizeof(data.toStdString().c_str()));
        lError = RegSetValueExA(hKey_handler, lpVal, 0, REG_SZ, (LPBYTE)(data.toStdString().c_str()), sizeof(data.toStdString().c_str()));
        RegCloseKey(hKey_handler);
        if (ERROR_SUCCESS == lError) {
            return 0;
        } else {
            return lError;
        }
    } else {
        return lError;
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

int WindowsReg::set_DWORD_value(HKEY _hKey, LPCSTR strSubKey, LPCSTR lpVal, DWORD _lpData){
    HKEY hKey_handler;

    LSTATUS lError = RegOpenKeyExA(_hKey, strSubKey, 0, KEY_ALL_ACCESS, &hKey_handler);
    if(ERROR_FILE_NOT_FOUND == lError) {
        lError = RegCreateKeyExA(_hKey, strSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey_handler, NULL);
    }

    if (ERROR_SUCCESS == lError) {
        lError = RegSetValueExA(hKey_handler, lpVal, 0, REG_DWORD, (LPBYTE)&_lpData, sizeof(DWORD));
        RegCloseKey(hKey_handler);
        if (ERROR_SUCCESS == lError) {
            return 0;
        } else {
            return lError;
        }
    } else {
        return lError;
    }
}
