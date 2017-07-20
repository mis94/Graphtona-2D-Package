#pragma once
#include "..\Algorithm.h"

class LineDrawer : public Algorithm
{
public:
	virtual void drawLine(HDC hdc, double xs, double ys, double xe, double ye) = 0;
};
