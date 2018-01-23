#pragma once
#include "CurveDrawer.h"

class BezierCurveDrawer : public CurveDrawer
{
public:
	void drawCurve(Point startPoint, Point endPoint, Point slopes[]);
};