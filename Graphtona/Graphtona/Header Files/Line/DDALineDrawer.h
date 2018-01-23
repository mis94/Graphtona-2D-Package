#pragma once
#include "LineDrawer.h"

class DDALineDrawer : public LineDrawer 
{
public:
	void drawLine(Point startPoint, Point endPoint);
};