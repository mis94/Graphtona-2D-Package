#pragma once
#include "..\Algorithm.h"

class LineDrawer : public Algorithm
{
public:
	virtual void drawLine(HDC hdc, Point startPoint, Point endPoint) = 0;
};
