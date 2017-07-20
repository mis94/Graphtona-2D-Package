#pragma once
#include "CircleDrawer.h"

class BresenhamCircleDrawer : public CircleDrawer
{
public:
	void drawCircle(HDC hdc, Point center, int radius);
};