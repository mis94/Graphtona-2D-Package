#pragma once
#include "..\Algorithm.h"
#include "..\Circle\BresenhamCircleDrawer.h"
#include "EdgeRecord.h"
#include "..\Line\ParametricLineDrawer.h"

class ConvexFiller : public Algorithm
{
public:
	void convexFill(HDC hdc, Point* points, int numberOfPoints);
	void fillCircle(HDC hdc, Point center, int radius);
};