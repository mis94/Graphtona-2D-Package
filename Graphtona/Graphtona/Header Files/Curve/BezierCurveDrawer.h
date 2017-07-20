#pragma once
#include "CurveDrawer.h"

class BezierCurveDrawer : public CurveDrawer
{
public:
	void drawCurve(HDC hdc, Point startPoint, Point endPoint, Point slopes[]);
};