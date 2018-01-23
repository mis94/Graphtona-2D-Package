#pragma once
#include "..\Algorithm.h"

class LineDrawer : public Algorithm
{
public:
	virtual void drawLine(Point startPoint, Point endPoint) = 0;
};
