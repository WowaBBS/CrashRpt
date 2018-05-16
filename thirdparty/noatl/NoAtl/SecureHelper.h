#pragma once

#include <stdio.h>
//#include <stdarg.h>

///////////////////////////////////////////////////////////////////////////////
// SecureHelper - helper functions for VS2005 secure CRT

namespace SecureHelper
{
	inline void memcpy_x(void* pDest, size_t cbDest, const void* pSrc, size_t cbSrc)
	{
#if _SECURE_ATL
		ATL::Checked::memcpy_s(pDest, cbDest, pSrc, cbSrc);
#else
		if(cbDest >= cbSrc)
			memcpy(pDest, pSrc, cbSrc);
		else
			ATLASSERT(FALSE);
#endif
	}

	inline void memmove_x(void* pDest, size_t cbDest, const void* pSrc, size_t cbSrc)
	{
#if _SECURE_ATL
		ATL::Checked::memmove_s(pDest, cbDest, pSrc, cbSrc);
#else
		if(cbDest >= cbSrc)
			memmove(pDest, pSrc, cbSrc);
		else
			ATLASSERT(FALSE);
#endif
	}

	inline int vsprintf_x(LPTSTR lpstrBuff, size_t cchBuff, LPCTSTR lpstrFormat, va_list args)
	{
#if _SECURE_ATL && !defined(_ATL_MIN_CRT) && !defined(_WIN32_WCE)
		return _vstprintf_s(lpstrBuff, cchBuff, lpstrFormat, args);
#else
		cchBuff;   // Avoid unused argument warning
#pragma warning(disable: 4996)
		//return _vstprintf(lpstrBuff, lpstrFormat, args);
  return vswprintf(lpstrBuff, cchBuff, lpstrFormat, args);
#pragma warning(default: 4996)
#endif
	}

	inline int wvsprintf_x(LPTSTR lpstrBuff, size_t cchBuff, LPCTSTR lpstrFormat, va_list args)
	{
#if _SECURE_ATL && !defined(_ATL_MIN_CRT) && !defined(_WIN32_WCE)
		return _vstprintf_s(lpstrBuff, cchBuff, lpstrFormat, args);
#else
		cchBuff;   // Avoid unused argument warning
		//return ::wvsprintf(lpstrBuff, lpstrFormat, args);
  return vswprintf(lpstrBuff, cchBuff, lpstrFormat, args);
#endif
	}

	inline int sprintf_x(LPTSTR lpstrBuff, size_t cchBuff, LPCTSTR lpstrFormat, ...)
	{
		va_list args;
		va_start(args, lpstrFormat);
		int nRes = vsprintf_x(lpstrBuff, cchBuff, lpstrFormat, args);
		va_end(args);
		return nRes;
	}

	inline int wsprintf_x(LPTSTR lpstrBuff, size_t cchBuff, LPCTSTR lpstrFormat, ...)
	{
		va_list args;
		va_start(args, lpstrFormat);
		int nRes = wvsprintf_x(lpstrBuff, cchBuff, lpstrFormat, args);
		va_end(args);
		return nRes;
	}
}
