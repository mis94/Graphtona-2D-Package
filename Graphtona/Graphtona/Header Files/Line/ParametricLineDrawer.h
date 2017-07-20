#pragma once
#include "LineDrawer.h"

class ParametricLineDrawer : public LineDrawer
{
public:
	void drawLine(HDC hdc, Point startPoint, Point endPoint);
};