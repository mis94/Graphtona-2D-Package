#pragma once
#include "CurveDrawer.h"

class HermiteCurveDrawer : public CurveDrawer
{
public:
	void drawCurve(HDC hdc, Point startPoint, Point endPoint, Point slopes[]);
	void drawSpline(HDC hdc, Point points[], int numberOfPoints, double c);
};