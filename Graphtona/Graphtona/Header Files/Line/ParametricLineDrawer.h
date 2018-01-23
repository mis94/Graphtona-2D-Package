#pragma once
#include "LineDrawer.h"

class ParametricLineDrawer : public LineDrawer
{
public:
	void drawLine(Point startPoint, Point endPoint);
};