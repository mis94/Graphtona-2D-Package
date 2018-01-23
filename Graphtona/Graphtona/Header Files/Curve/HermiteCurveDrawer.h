#pragma once
#include "CurveDrawer.h"

class HermiteCurveDrawer : public CurveDrawer
{
public:
	void drawCurve(Point startPoint, Point endPoint, Point slopes[]);
	void drawSpline(Point points[], int numberOfPoints, double c);
};