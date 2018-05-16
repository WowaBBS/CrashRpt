#pragma once

#include "CPoint.h"
#include "CRect.h"
#include "CSize.h"

// CSize implementation

inline CPoint CSize::operator +(POINT point) const
{ return CPoint(cx + point.x, cy + point.y); }

inline CPoint CSize::operator -(POINT point) const
{ return CPoint(cx - point.x, cy - point.y); }

inline CRect CSize::operator +(const RECT* lpRect) const
{ return CRect(lpRect) + *this; }

inline CRect CSize::operator -(const RECT* lpRect) const
{ return CRect(lpRect) - *this; }
