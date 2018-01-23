#pragma once
#include "..\Algorithm.h"

class CircleDrawer : public Algorithm
{
public:
	virtual void drawCircle(Point center, int radius) = 0;
	void draw8Points(Point center, int a, int b);
};
