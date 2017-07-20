#pragma once
#include "LineDrawer.h"

class BresenhamLineDrawer : public LineDrawer
{
public:
	void drawLine(HDC hdc, Point startPoint, Point endPoint);
};