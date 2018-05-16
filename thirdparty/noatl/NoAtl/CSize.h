#pragma once

class CPoint;
class CRect;

///////////////////////////////////////////////////////////////////////////////
// CSize - Wrapper for Windows SIZE structure.

class CSize : public SIZE
{
public:
// Constructors
  CSize()
  {
    cx = 0;
    cy = 0;
  }

  CSize(int initCX, int initCY)
  {
    cx = initCX;
    cy = initCY;
  }

  CSize(SIZE initSize)
  {
    *(SIZE*)this = initSize;
  }

  CSize(POINT initPt)
  {
    *(POINT*)this = initPt;
  }

  CSize(DWORD dwSize)
  {
    cx = (short)LOWORD(dwSize);
    cy = (short)HIWORD(dwSize);
  }

// Operations
  BOOL operator ==(SIZE size) const
  {
    return (cx == size.cx && cy == size.cy);
  }

  BOOL operator !=(SIZE size) const
  {
    return (cx != size.cx || cy != size.cy);
  }

  void operator +=(SIZE size)
  {
    cx += size.cx;
    cy += size.cy;
  }

  void operator -=(SIZE size)
  {
    cx -= size.cx;
    cy -= size.cy;
  }

  void SetSize(int CX, int CY)
  {
    cx = CX;
    cy = CY;
  }

// Operators returning CSize values
  CSize operator +(SIZE size) const
  {
    return CSize(cx + size.cx, cy + size.cy);
  }

  CSize operator -(SIZE size) const
  {
    return CSize(cx - size.cx, cy - size.cy);
  }

  CSize operator -() const
  {
    return CSize(-cx, -cy);
  }

// Operators returning CPoint values
  CPoint operator +(POINT point) const;
  CPoint operator -(POINT point) const;

// Operators returning CRect values
  CRect operator +(const RECT* lpRect) const;
  CRect operator -(const RECT* lpRect) const;
};
