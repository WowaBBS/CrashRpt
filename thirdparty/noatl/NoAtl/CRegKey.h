#pragma once

// Token from WLib\Sys\Api\Win32\Kernel\Thread\CrSect.h

class CRegKey
{
public:
  LONG Open(
    HKEY hKeyParent,
    LPCTSTR lpszKeyName,
    REGSAM samDesired = KEY_READ | KEY_WRITE)
  {
    return 0;
  }
  
  LONG Close() { return 0; }
  
  LONG QueryValue(  
    LPCTSTR pszValueName,
    DWORD* pdwType,
    void* pData,
    ULONG* pnBytes)
  { return 0; }

  LONG QueryValue( //ATL_DEPRECATED 
    DWORD& dwValue,
    LPCTSTR lpszValueName)
  { return 0; }

  LONG QueryValue( //ATL_DEPRECATED 
    LPTSTR szValue,
    LPCTSTR lpszValueName,
    DWORD* pdwCount)
  { return 0; }
};
