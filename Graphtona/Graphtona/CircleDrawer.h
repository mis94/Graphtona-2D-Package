#pragma once
#include "Algorithm.h"

class CircleDrawer : public Algorithm
{
public:
	virtual void drawCircle(HDC hdc, double xc, double yc, int radius) = 0;

	void draw8Points(HDC hdc, double xc, double yc, int a, int b)
	{
		SetPixel(hdc, xc + a, yc + b, RGB(0, 0, 0));
		SetPixel(hdc, xc - a, yc + b, RGB(0, 0, 0));
		SetPixel(hdc, xc + a, yc - b, RGB(0, 0, 0));
		SetPixel(hdc, xc - a, yc - b, RGB(0, 0, 0));
		SetPixel(hdc, xc + b, yc + a, RGB(0, 0, 0));
		SetPixel(hdc, xc - b, yc + a, RGB(0, 0, 0));
		SetPixel(hdc, xc + b, yc - a, RGB(0, 0, 0));
		SetPixel(hdc, xc - b, yc - a, RGB(0, 0, 0));
	}
};
