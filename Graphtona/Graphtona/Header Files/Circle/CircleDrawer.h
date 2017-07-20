#pragma once
#include "..\Algorithm.h"

class CircleDrawer : public Algorithm
{
public:
	virtual void drawCircle(HDC hdc, Point center, int radius) = 0;
	void draw8Points(HDC hdc, Point center, int a, int b);
};
