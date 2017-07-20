#pragma once
#include "Algorithm.h"

class EllipseDrawer : public Algorithm
{
public:
	void drawEllipse(HDC hdc, int xc, int yc, int width, int height);
};