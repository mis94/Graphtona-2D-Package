#pragma once
#include "CurveDrawer.h"

class FirstDegreeCurveDrawer : public CurveDrawer
{
public:
	void drawCurve(Point startPoint, Point endPoint, Point slopes[]);
};