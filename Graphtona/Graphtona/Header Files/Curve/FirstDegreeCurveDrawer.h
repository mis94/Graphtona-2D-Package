#pragma once
#include "CurveDrawer.h"

class FirstDegreeCurveDrawer : public CurveDrawer
{
public:
	void drawCurve(HDC hdc, Point startPoint, Point endPoint, Point slopes[]);
};