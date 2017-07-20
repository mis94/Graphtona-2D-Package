#pragma once
#include "CircleDrawer.h"

class BasicPolarCircleDrawer : public CircleDrawer
{
public:
	void drawCircle(HDC hdc, double xc, double yc, int radius);
};