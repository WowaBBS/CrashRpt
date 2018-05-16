#pragma once

#include "CSize.h"
#include "CPoint.h"

class CRect;

///////////////////////////////////////////////////////////////////////////////
// CPoint - Wrapper for Windows POINT structure.

class CPoint : public POINT
{
public:
// Constructors
  CPoint()
  {
    x = 0;
    y = 0;
  }

  CPoint(int initX, int initY)
  {
    x = initX;
    y = initY;
  }

  CPoint(POINT initPt)
  {
    *(POINT*)this = initPt;
  }

  CPoint(SIZE initSize)
  {
    *(SIZE*)this = initSize;
  }

  CPoint(DWORD dwPoint)
  {
    x = (short)LOWORD(dwPoint);
    y = (short)HIWORD(dwPoint);
  }

// Operations
  void Offset(int xOffset, int yOffset)
  {
    x += xOffset;
    y += yOffset;
  }

  void Offset(POINT point)
  {
    x += point.x;
    y += point.y;
  }

  void Offset(SIZE size)
  {
    x += size.cx;
    y += size.cy;
  }

  BOOL operator ==(POINT point) const
  {
    return (x == point.x && y == point.y);
  }

  BOOL operator !=(POINT point) const
  {
    return (x != point.x || y != point.y);
  }

  void operator +=(SIZE size)
  {
    x += size.cx;
    y += size.cy;
  }

  void operator -=(SIZE size)
  {
    x -= size.cx;
    y -= size.cy;
  }

  void operator +=(POINT point)
  {
    x += point.x;
    y += point.y;
  }

  void operator -=(POINT point)
  {
    x -= point.x;
    y -= point.y;
  }

  void SetPoint(int X, int Y)
  {
    x = X;
    y = Y;
  }

// Operators returning CPoint values
  CPoint operator +(SIZE size) const
  {
    return CPoint(x + size.cx, y + size.cy);
  }

  CPoint operator -(SIZE size) const
  {
    return CPoint(x - size.cx, y - size.cy);
  }

  CPoint operator -() const
  {
    return CPoint(-x, -y);
  }

  CPoint operator +(POINT point) const
  {
    return CPoint(x + point.x, y + point.y);
  }

// Operators returning CSize values
  CSize operator -(POINT point) const
  {
    return CSize(x - point.x, y - point.y);
  }

// Operators returning CRect values
  CRect operator +(const RECT* lpRect) const;
  CRect operator -(const RECT* lpRect) const;
};
