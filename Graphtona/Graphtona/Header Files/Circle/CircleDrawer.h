#pragma once
#include "..\Algorithm.h"

class CircleDrawer : public Algorithm
{
public:
	virtual void drawCircle(HDC hdc, double xc, double yc, int radius) = 0;
	void draw8Points(HDC hdc, double xc, double yc, int a, int b);
};
