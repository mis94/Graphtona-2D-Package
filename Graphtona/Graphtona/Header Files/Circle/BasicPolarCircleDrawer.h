#pragma once
#include "CircleDrawer.h"

class BasicPolarCircleDrawer : public CircleDrawer
{
public:
	void drawCircle(HDC hdc, Point center, int radius);
};