#pragma once
#include "LineDrawer.h"

class ParametricLineDrawer : public LineDrawer
{
public:
	void drawLine(HDC hdc, double xs, double ys, double xe, double ye);
};