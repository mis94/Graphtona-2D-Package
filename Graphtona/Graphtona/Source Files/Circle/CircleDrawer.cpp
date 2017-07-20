#include "..\..\Header Files\Circle\CircleDrawer.h"

void CircleDrawer::draw8Points(HDC hdc, double xc, double yc, int a, int b)
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