#pragma once
#include "CurveDrawer.h"

class SecondDegreeCurveDrawer : public CurveDrawer
{
public:
	void drawCurve(HDC hdc, Point startPoint, Point endPoint, Point slopes[]);
};
