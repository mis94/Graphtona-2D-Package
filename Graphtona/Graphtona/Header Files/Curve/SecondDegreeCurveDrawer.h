#pragma once
#include "CurveDrawer.h"

class SecondDegreeCurveDrawer : public CurveDrawer
{
public:
	void drawCurve(Point startPoint, Point endPoint, Point slopes[]);
};
