#pragma once
#include "CircleDrawer.h"

class CartesianCircleDrawer : public CircleDrawer
{
public:
	void drawCircle(HDC hdc, Point center, int radius);
};