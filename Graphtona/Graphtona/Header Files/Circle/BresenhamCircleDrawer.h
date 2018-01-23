#pragma once
#include "CircleDrawer.h"

class BresenhamCircleDrawer : public CircleDrawer
{
public:
	void drawCircle(Point center, int radius);
};