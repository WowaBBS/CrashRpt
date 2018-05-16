#pragma once

#include <tchar.h>
#include <wchar.h>

#define _ATL_MIN_CRT

///////////////////////////////////////////////////////////////////////////////
// MinCrtHelper - helper functions for using _ATL_MIN_CRT

namespace MinCrtHelper
{
	inline int _isspace(TCHAR ch)
	{
#ifndef _ATL_MIN_CRT
		return _istspace(ch);
#else // _ATL_MIN_CRT
		WORD type = 0;
		::GetStringTypeEx(::GetThreadLocale(), CT_CTYPE1, &ch, 1, &type);
		return (type & C1_SPACE) == C1_SPACE;
#endif // _ATL_MIN_CRT
	}

	inline int _isdigit(TCHAR ch)
	{
#ifndef _ATL_MIN_CRT
		return _istdigit(ch);
#else // _ATL_MIN_CRT
		WORD type = 0;
		::GetStringTypeEx(::GetThreadLocale(), CT_CTYPE1, &ch, 1, &type);
		return (type & C1_DIGIT) == C1_DIGIT;
#endif // _ATL_MIN_CRT
	}

	inline int _atoi(LPCTSTR str)
	{
#ifndef _ATL_MIN_CRT
		return _ttoi(str);
#else // _ATL_MIN_CRT
		while(_isspace(*str) != 0)
			++str;

		TCHAR ch = *str++;
		TCHAR sign = ch;   // save sign indication
		if(ch == _T('-') || ch == _T('+'))
			ch = *str++;   // skip sign

		int total = 0;
		while(_isdigit(ch) != 0)
		{
			total = 10 * total + (ch - '0');   // accumulate digit
			ch = *str++;        // get next char
		}

		return (sign == '-') ? -total : total;   // return result, negated if necessary
#endif // _ATL_MIN_CRT
	}

	inline LPCTSTR _strrchr(LPCTSTR str, TCHAR ch)
	{
#ifndef _ATL_MIN_CRT
		return _tcsrchr(str, ch);
#else // _ATL_MIN_CRT
		LPCTSTR lpsz = NULL;
		while(*str != 0)
		{
			if(*str == ch)
				lpsz = str;
			str = ::CharNext(str);
		}
		return lpsz;
#endif // _ATL_MIN_CRT
	}

	inline LPTSTR _strrchr(LPTSTR str, TCHAR ch)
	{
#ifndef _ATL_MIN_CRT
		return _tcsrchr(str, ch);
#else // _ATL_MIN_CRT
		LPTSTR lpsz = NULL;
		while(*str != 0)
		{
			if(*str == ch)
				lpsz = str;
			str = ::CharNext(str);
		}
		return lpsz;
#endif // _ATL_MIN_CRT
	}
}; // namespace MinCrtHelper
