#pragma once

#include <string>
#include <tchar.h>
#include <cstdlib>
#include <memory> 

struct CString: std::wstring
{
  typedef CString Self;
  typedef std::wstring Parent;
  
  inline CString(){}
  inline CString(const Self   &v) : Parent(v) {}
  inline CString(const Parent &v) : Parent(v) {}
  inline CString(      LPCTSTR v) : Parent(v? v:L"") { }
  inline CString(const char   *v) { if(v) assign(v, v+strlen(v)); else Empty(); }
  
  inline       Parent& _Str()       { return *this; }
  inline const Parent& _Str() const { return *this; }
  
//inline operator LPCTSTR() const { return c_str(); }
  inline operator LPCWSTR() const { return c_str(); }
  inline TCHAR operator[](int i) { return _Str()[i]; }
  
  inline bool IsEmpty() const { return length()==0; }
  inline int GetLength() const { return length(); }
  
  template<class T> int ReverseFind(const T &m) const { auto Res= rfind(m); return Res==npos? -1: Res; }
  template<class T> int Find(const T &m, int Start=0) const { auto Res=  find(m, Start); return Res==npos? -1: Res; }
  inline int FindOneOf(LPCTSTR lpszCharSet) const
  {
    LPCTSTR lpsz = wcspbrk(c_str(), lpszCharSet);
    return (lpsz == NULL) ? -1:(int)(lpsz-c_str());
  }
  
  inline Self Left(int nCount) const { return substr(0, nCount); }
  inline Self Mid(int iFirst, int nCount) const { return substr(iFirst, nCount);}
  inline Self Mid(int iFirst) const  { return substr(iFirst, length()-iFirst);}
  inline Self Right(int nCount) const { int l=length(), i=l-nCount; return substr(i<0? 0:i, l-1); }
  
  CString SpanIncluding(LPCTSTR CharSet) const { return Left(wcsspn  (c_str(), CharSet)); }
  CString SpanExcluding(LPCTSTR CharSet) const { return Left(wcscspn (c_str(), CharSet)); }

  inline Self& operator+= (const Parent  &v) { _Str()+=v; return *this; }
  inline Self& operator+= (const wchar_t *v) { _Str()+=v; return *this; }
  inline Self& operator+= (      wchar_t  v) { _Str()+=v; return *this; }

  template<class T>
  inline Self operator+ (const T &v) const { return _Str()+v; }
  
  inline int Replace(const wchar_t *pszOld, const wchar_t *pszNew)
  {
    int ol=wcslen(pszOld);
    int i=0;
    int Res=0;
    while(true)
    {
      i=Find(pszOld,i);
      if(i<0)
        break;
      replace(i, ol, pszNew);
      Res++;
      i++;
    }
    return Res;
  }
  
  inline int Replace(wchar_t chOld, wchar_t chNew)
  {
    int Res=0;
    for(int i=0, l=length(); i<l; i++)
    {
    //wchar_t &c=(*this)[i];
    //wchar_t &c=c_str()[i];
      wchar_t &c=at(i);
      if(c!=chOld)
        continue;
      c=chNew;
      Res++;
    }
    return Res;
  }
  
  inline int Compare(LPCTSTR lpsz) const   // straight character (MBCS/Unicode aware)
  {
    return compare(lpsz);
  }

  inline bool operator !=(wchar_t c) const
  {
    return length()!=1 || c_str()[0]!=c;
  }
  
  inline bool operator ==(wchar_t c) const
  {
    return length()==1 && c_str()[0]==c;
  }
  
  
//inline Self& TrimLeft(XCHAR chTarget);
//inline Self& TrimLeft(PCXSTR pszTargets);
  inline Self& TrimLeft()
  {
    int i=0;
    for(int c=length(); i<c && (*this)[i]==' '; i++)
    erase(0, i);
    return *this;
  }

  Self& TrimRight()
  {
    int c=length();
    int i=c-1;
    for(; i<=0 && (*this)[i]==' '; i++)
    erase(i+1);
    return *this;
  }

  void Format(const wchar_t *fmt_str, ...)
  {
    va_list ap;
    va_start(ap, fmt_str);
    const int MaxLen=1024*4;
    wchar_t Res[MaxLen];
    int Len = vswprintf(Res, MaxLen, fmt_str, ap);
    va_end(ap);
    *this=Res;
  }
/*  
  void Format(const Self &fmt_str, ...)
  {
    int final_n, n = ((int)fmt_str.size()) * 2; // Reserve two times as much as the length of the fmt_str
    std::unique_ptr<wchar_t[]> formatted;
    va_list ap;
    while(1)
    {
        formatted.reset(new wchar_t[n]); // Wrap the plain char array into the unique_ptr
        wcscpy(&formatted[0], fmt_str.c_str());
      //strcpy(&formatted[0], fmt_str.c_str());
        va_start(ap, fmt_str);
        final_n = vswprintf(&formatted[0], n, fmt_str.c_str(), ap);
        va_end(ap);
        if (final_n < 0 || final_n >= n)
            n += abs(final_n - n + 1);
        else
            break;
    }
    *this=formatted.get();
  }
*/  
  LPTSTR GetBuffer(int nMinBufLength)
  {
    if(length()<nMinBufLength)
      resize(nMinBufLength);
    return &at(0);
  }

  void Empty()   // free up the data
  {
    clear();
  }
  
  void ReleaseBuffer(int nNewLength=-1)
  {
    if(nNewLength<0)
      nNewLength=wcslen(c_str());
    resize(nNewLength);
  }
/**/
};
