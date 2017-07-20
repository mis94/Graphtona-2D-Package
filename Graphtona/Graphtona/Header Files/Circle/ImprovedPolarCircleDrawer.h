#pragma once
#include "CircleDrawer.h"

class ImprovedPolarCircleDrawer : public CircleDrawer
{
public:
	void drawCircle(HDC hdc, Point center, int radius);
};