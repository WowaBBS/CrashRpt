#pragma once

#include "CRect.h"
#include "CPoint.h"
// CPoint implementation

inline CRect CPoint::operator +(const RECT* lpRect) const { return CRect(lpRect) + *this; }
inline CRect CPoint::operator -(const RECT* lpRect) const { return CRect(lpRect) - *this; }
