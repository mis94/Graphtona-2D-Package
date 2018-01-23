#pragma once
#include "..\Algorithm.h"
#include "..\Circle\BresenhamCircleDrawer.h"
#include "EdgeRecord.h"
#include "..\Line\BresenhamLineDrawer.h"

class ConvexFiller : public Algorithm
{
public:
	void convexFill(Point* points, int numberOfPoints);
	void fillCircle(Point center, int radius);
};