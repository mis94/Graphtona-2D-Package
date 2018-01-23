#pragma once
#include "LineDrawer.h"

class BresenhamLineDrawer : public LineDrawer
{
public:
	void drawLine(Point startPoint, Point endPoint);
};