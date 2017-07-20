#pragma once
#include "LineDrawer.h"

class DDALineDrawer : public LineDrawer 
{
public:
	void drawLine(HDC hdc, Point startPoint, Point endPoint);
};